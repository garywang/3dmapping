#include <ctime>
#include <iostream>
#include "kht.h"

// Image files.
struct binary_image_t
{
	// Pixels buffer size (in bytes).
	size_t buffer_size;

	// Image file path.
	const char *filename;
	
	// Image pixels.
	unsigned char *pixels;

	// Image pixels copy.
	unsigned char *pixels_copy;

	// Image dimentions.
	size_t width;
	size_t height;

	// Number of relevant lines to be displayed.
	size_t relevant_lines;

	// Class constructor.
	binary_image_t() :
		buffer_size(0),
		filename(0),
		height(0),
		pixels(0),
		pixels_copy(0),
		relevant_lines(0),
		width(0)
	{
	}

	// Class destructor.
	~binary_image_t()
	{
		free( pixels );
		free( pixels_copy );
	}
};

// Specifies a list of binary images.
static list<binary_image_t,1> images_list;

// Specifies the image to be processed.
static size_t current_image_index = 0;

// Frame rate.
static double frame_rate = 0.0;

// pi value.
static const double pi = 3.14159265358979323846;

// The main function.
int main(int argc, char *argv[])
{
	// Load input binary images.
	static const size_t images_count = 8;
	static const char *filenames[images_count]={
		"./images/chess_binary.bmp",
		"./images/road_binary.bmp",
		"./images/wall_binary.bmp",
		"./images/board_binary.bmp",
		"./images/church_binary.bmp",
		"./images/building_binary.bmp",
		"./images/beach_binary.bmp",
		"./images/simple_binary.bmp"
	};
	static const size_t relevant_lines[images_count]={
		25,
		15,
		36,
		38,
		40,
		19,
		19,
		8
	};

	for (size_t i=0; i!=images_count; ++i)
	{
		ILuint devil_id = ilGenImage();
		ilBindImage( devil_id );

		std::cout << "Loading image '" << filenames[i] << "'... ";

		if (ilLoadImage( filenames[i] ))
		{
			binary_image_t &binary_image = images_list.push_back();

			// Convert image to single channel.
			ilConvertImage( IL_LUMINANCE, IL_BYTE );
			
			// Get image data.
			binary_image.devil_id = devil_id;

			binary_image.filename = filenames[i];
			binary_image.relevant_lines = relevant_lines[i];

			binary_image.width = ilGetInteger( IL_IMAGE_WIDTH );
			binary_image.height = ilGetInteger( IL_IMAGE_HEIGHT );
			
			binary_image.buffer_size = binary_image.height * binary_image.width * sizeof( unsigned char );
			binary_image.pixels = static_cast<unsigned char*>( malloc( binary_image.buffer_size ) );
			binary_image.pixels_copy = static_cast<unsigned char*>( malloc( binary_image.buffer_size ) );
			
			memcpy( binary_image.pixels, ilGetData(), binary_image.buffer_size );
			memset( binary_image.pixels_copy, 0, binary_image.buffer_size );

			std::cout << "done." << std::endl;
		}
		else
		{
			std::cout << "error." << std::endl;
		}
	}
	/*
	binary_image_t *image = (!images_list.empty()) ? &images_list[current_image_index] : NULL;
	
	if (image)
	{
		// Execute the proposed Hough transform voting scheme and the peak detection procedure.
		static lines_list_t lines;

		memcpy( image->pixels_copy, image->pixels, image->buffer_size );
		kht( lines, image->pixels_copy, image->width, image->height, 10, 2.0, 0.5, 0.002, 2 );
	}
	*/
	return 0;
}