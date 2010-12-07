/*
 *  MacImageManager.h
 *  Bme
 *
 *  Created by Tim De Jong on 18-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MAC_IMAGE_MANAGER_H
#define MAC_IMAGE_MANAGER_H

#include "IImageManager.h"
#include "Image.h"

class MacImageManager : public IImageManager
{
public:
	MacImageManager();
	virtual ~MacImageManager();
		
	virtual void*	GetUIBitmapFromImage(Image* image);
	virtual Image*	GetImageFromFile(std::string filename);
	virtual Image*	GetImageFromBytes(const uint8_t *bytes, uint8_t length);
	
private:
	std::string GetUniqueImageId(std::string filename);
	Image* GetNewImage(NSImage* image, std::string filename = "");
	
private:
	NSMutableDictionary* m_images;
};

#endif