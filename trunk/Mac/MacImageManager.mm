/*
 *  MacImageManager.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 18-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MacImageManager.h"
#include <stdlib.h>

MacImageManager::MacImageManager()
					:	IImageManager()
{
	m_images = [[NSMutableDictionary alloc] initWithCapacity:10];
}

MacImageManager::~MacImageManager()
{
	[m_images release];
}

void* MacImageManager::GetUIBitmapFromImage(Image* image)
{
	NSString* imageId = [[NSString alloc] initWithCString:(image->ImageId()).c_str()];	
	NSImage* newImage = [m_images objectForKey:imageId];
	[imageId release];
	
	return newImage;
}

Image* MacImageManager::GetImageFromFile(std::string filename)
{
	NSString* imageFilename = [[NSString alloc] initWithCString:filename.c_str()];
	NSImage* newImage = [[NSImage alloc] initWithContentsOfFile:imageFilename];
	
	Image* img = this->GetNewImage(newImage, filename);
	
	[newImage release];
	[imageFilename release];	
	
	return img;
}

Image* MacImageManager::GetImageFromBytes(const uint8_t *bytes, uint8_t length)
{	
	NSData* data = [[NSData alloc] initWithBytes:(void*)bytes length:length];
	NSImage* newImage = [[NSImage alloc] initWithData:data];
	
	Image* img = this->GetNewImage(newImage);
	
	[data release];	
	[newImage release];
	
	return img; 
}

std::string MacImageManager::GetUniqueImageId(std::string filename)
{	
	//generate a unique filename here
	NSDate* date = [NSDate date];
	//first, get a randomnumber
	long randomNumber = random();
	//append this number to the current date
	NSString* uniqueString = [[NSString alloc] initWithFormat:@"%@-%d-", [date description], randomNumber];
	const char* cString = [uniqueString cStringUsingEncoding:NSASCIIStringEncoding];
	[uniqueString release];
	//add the filename to the end of the string (if available)
	std::string uniqueName(cString);
	uniqueName += filename;
	return uniqueName;
}

Image* MacImageManager::GetNewImage(NSImage* image, std::string filename)
{
	//get a unique identifier for this image
	std::string uniqueId = this->GetUniqueImageId(filename);
	//make a new Image object containing the uniqueId
	NSSize imageSize = [image size];
	Image* img = new Image(uniqueId, imageSize.width, imageSize.height); //add method to generate unique image ID
	//convert unique id into Objective C string
	NSString* uniqueImageId = [[NSString alloc] initWithCString:uniqueId.c_str() encoding:NSASCIIStringEncoding];
	[m_images setObject:image forKey:uniqueImageId];
	[uniqueImageId release];
	
	return img;
}
