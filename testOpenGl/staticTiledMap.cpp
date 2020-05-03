#include "staticTiledMap.hpp"

const unsigned int lookup[6] = { 0,1,2,2,3,1 };

void staticTiledMap::readFromFile(std::ifstream& f, laen::map<Texture>& textures)
{
	//TODO, finish this implementation
	std::string currentLine;
	int multX = 1;
	int multY = 1;
	int tmpX;
	int tmpY;
	int width = -1;
	int height = -1;
	std::map<std::string, int> names;
	std::string dummy;
	std::string name;
	std::string fileName;
	while (getline(f, currentLine)) {
		std::string processed = "";
		FORI(i, currentLine.size(),
			char c = currentLine[i];
		if ((c != '\t'))
			processed+=c;
			)
			if (processed.size() == 0) {
				continue;
			}

			std::istringstream iss(processed);
			if (0 == processed.find("#textureFile")) {
				std::cout << "textureFile ! " << std::endl;
				iss >> dummy;
				iss >> name;
				iss >> fileName;
				fileName = "res/texture/" + fileName;
#ifdef DEBUG
				std::cout << "creating texture " << fileName << " " << name << std::endl;
#endif
				Texture* tmp = new Texture(fileName, name);
				textures.putObject(name, tmp);
				this->texture = tmp;
			}
			if (0 == processed.find("#multiplierXY")) {
				iss >> dummy;
				iss >> multX;
				iss >> multY;
#ifdef DEBUG
				std::cout << "setting scale " << multX << " " << multY << std::endl;
#endif
			}
			if (0 == processed.find("#tileTexture")) {
				iss >> dummy;
				iss >> name;
				iss >> tmpX;
				iss >> tmpY;
				names[name] = 0;
				this->textures.putObject(name, new tileTexture(this->texture, tmpX * multX, tmpY * multY,  multX,  multY, name));
#ifdef DEBUG
				std::cout << "* texture " << name << " " << tmpX * multX << " " <<  tmpY * multY<< " " <<  multX<< " " <<   multY << " " << name << std::endl;
#endif
				continue;
			}
			if (0 == processed.find("#width")) {
				iss >> dummy;
				iss >> width;
				width *= multX;
				if (height > 0 && width > 0) {
					this->cam = new Camera2D(0, 0, width, height);
#ifdef DEBUG
					std::cout << "creating camera " << width  << " " << height<< std::endl;
#endif
				}
#ifdef DEBUG
				std::cout << "setting width of camera " << width << std::endl;
#endif
			}
			if (0 == processed.find("#height")) {
				iss >> dummy;
				iss >> height;
				height *= multY;
				if (height > 0 && width > 0) {
					this->cam = new Camera2D(0, 0, width, height);
#ifdef DEBUG
					std::cout << "creating camera " << width << " " << height << std::endl;
#endif
				}
#ifdef DEBUG
				std::cout << "setting height of camera " << height << std::endl;
#endif
			}
			if (0 == processed.find("#tile")) {
				iss >> dummy;
				iss >> name;
				iss >> tmpX;
				iss >> tmpY;
				tmpX *= multX;
				tmpY *= multY;
				tileTexture* tileTex = this->textures.getByName(name);
				std::stringstream ss;
				ss << name << "_" << names[name]++;
				ss >> name;
#ifdef DEBUG
				std::cout << "creating tile" << name << std::endl;
#endif
				elements.putObject(name,new staticTile(this->cam, tileTex, tmpX, tmpY, multX, multY, name));
			}
	}
}

int staticTiledMap::getWidth()
{
	return width;
}

int staticTiledMap::getHeight()
{
	return height;
}

void staticTiledMap::draw()
{
	if (this->camshot != this->cam->getCurrentShot()) {
		int numberDraw = 0;
		for (auto it = elements.begin(); it != elements.end(); it++) {
			if (it->second->getShouldRender())
				numberDraw++;
		}
		this->dataLength = numberDraw * 16;//the 16 can change in the future
		DELETA(this->vertices);
		DELETA(this->indexes);
		
		this->vertices = new float[dataLength];
		this ->indexesLength = numberDraw * 6;
		this->indexes = new unsigned int[indexesLength];
		int current = 0;
		for (auto it = elements.begin(); it != elements.end(); it++) {
			if (it->second->getShouldRender()) {
				it->second->computeAll();
				it->second->putInArray(vertices, current * 16, 4);
				++current;
			}
		}
		FORI(i, indexesLength,
			this->indexes[i] = (i/6) * 4 + lookup[i % 6];
			)
		this->camshot = this->cam->getCurrentShot();
		this->vaib->setData((float*)vertices, this->dataLength);
		this->vaib->setIndexes((unsigned int*)indexes, indexesLength);
	}
	
	this->texture->bind(0);
	this->vaib->draw();

}

Camera2D * staticTiledMap::getCamera()
{
	return cam;
}

staticTiledMap::staticTiledMap(std::string path, laen::map<Texture>& textures)
{
	std::ifstream in(path);
	this->readFromFile(in, textures);
	int shape[2] = { 2,2 };
	int numberDraw = 0;
	for (auto it = elements.begin(); it != elements.end(); it++) {
		if (it->second->getShouldRender())
			numberDraw++;
	}
	this->dataLength = numberDraw *16;//the 16 can change in the future
	this->indexesLength = numberDraw * 6;
	this->vertices = new float[dataLength];
	
	int current = 0;
	this->indexes = new unsigned int [indexesLength];
	for (auto it = elements.begin(); it != elements.end(); it++) {
		if (it->second->getShouldRender()) {
			it->second->computeAll();
			it->second->putInArray(vertices, current * 16, 4);
			++current;
		}
	}
	FORI(i, indexesLength,
		this->indexes[i] = (i / 6) * 4 + lookup[i % 6];
	)
	this->vaib = new VertexAndIndexBuffer(shape, 2, vertices, dataLength, GL_DYNAMIC_DRAW, indexes, indexesLength);
	this->camshot = this->cam->getCurrentShot();
}


staticTiledMap::~staticTiledMap()
{
	std::cout << "deleting this tiled Map " << std::endl;
	delete this->cam;
	delete this->vaib;
	DELETA(indexes);
	DELETA(vertices);
}
