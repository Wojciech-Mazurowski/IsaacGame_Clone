#pragma once
class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();

	void loadAll();

	void findDefaultPath();
	void loadFonts();
	void loadTextures();
};

