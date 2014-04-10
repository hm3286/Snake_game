
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <sstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>

/*himanshu and ashish*/
#define MX 640
#define MY 480
#define H 16/* height of my image*/
#define W 16/* width of my image*/
#define S 16/* space between boundary and screen*/
#define T 10/* seconds for bonus fruit*/

int main_himanshu();
bool wel(int);/* welcome screen*/
void basic(int);/*basically draws boundary and first fruit*/
bool mane();/* does the rest of main work*/
void print(char);/* print snake on screen (called inside mane) */
//SDL_Surface* screen  =NULL;/* for the screen*/
SDL_Surface* welcome =NULL;// for the welcome message or image
SDL_Surface* head    =NULL;
SDL_Surface* body    =NULL;
SDL_Surface* tail    =NULL;
SDL_Surface* headu   =NULL;
SDL_Surface* headd   =NULL;
SDL_Surface* headr   =NULL;
SDL_Surface* headl   =NULL;
SDL_Surface* bodyu   =NULL;
SDL_Surface* bodyl   =NULL;
SDL_Surface* tailu   =NULL;
SDL_Surface* taild   =NULL;
SDL_Surface* taill   =NULL;
SDL_Surface* tailr   =NULL;
SDL_Surface* bendul  =NULL;
SDL_Surface* bendur  =NULL;
SDL_Surface* benddl  =NULL;
SDL_Surface* benddr  =NULL;
SDL_Surface* b1      =NULL;
SDL_Surface* f1      =NULL;
SDL_Surface* bf1     =NULL;
SDL_Surface* clear   =NULL;// the  that clears the snakes last position
SDL_Surface* clear2  =NULL;//for score
//SDL_Event event;

//TTF_Font *font = NULL;// for welcome message
SDL_Color textColor = { 255, 255, 255 };// color of welcome message

bool quit = false,running=false;//state of timer( running or stopped)
int a[100],b[100],t=-1,t2=-1,p,q,p1=0,q1=0,ltx,lty,fruits=0,bfruits=0;// no. of fruits eaten
int o1[1000],o2[1000],tb=-1,tb2=-1;
int levscore[7],tlev=-1;// verma
Uint32 start;




//all my variables

Mix_Chunk *click = NULL;
SDL_Surface* im = NULL;
SDL_Surface* button = NULL;
SDL_Surface* cover = NULL;
SDL_Surface* screen = NULL;
SDL_Surface *message = NULL; // To accept name from user
SDL_Surface *background = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 24;

SDL_Event event;
SDL_Event event_p;
SDL_Event event_c;
SDL_Event event_h; //event for func name _handle
TTF_Font *font = NULL;
//SDL_Color textColor = { 0x00, 0x00, 0x00 };
//****************
int f;//junk variables

bool file(char name[20], int s, int n); //handles file handling

bool name_handle(); //handles name input by user
//function applies surface on screen

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );

SDL_Surface *load_image( std::string filename ); //loads image from destination to memory


int s;
char abv[40];

int n;
int k;

class StringInput //Class to get name of user
{
    private:
    //The storage string
    std::string str;

    //The text surface
    SDL_Surface *text;

    public:
    //Initializes variables
    StringInput();

    //Does clean up
    ~StringInput();

    //Handles input
    void handle_input();

    //Shows the message on screen
    void show_centered();
}  ;
StringInput::StringInput()
{
    //Initialize the string
    str = "";

    //Initialize the surface
    text = NULL;

    //Enable Unicode
    SDL_EnableUNICODE( SDL_ENABLE );
}

StringInput::~StringInput()
{
    //Free text surface
    SDL_FreeSurface( text );

    //Disable Unicode
    SDL_EnableUNICODE( SDL_DISABLE );
}

void StringInput::handle_input()  //function to accept name from user
{
    //If a key was pressed
    if( event_h.type == SDL_KEYDOWN )
    {
        //Keep a copy of the current version of the string
        std::string temp = str;

        //If the string less than maximum size
        if( str.length() <= 16 )
        {
            //If the key is a space
            if( event_h.key.keysym.unicode == (Uint16)' ' )
            {
                //Append the character
                str += (char)event_h.key.keysym.unicode;
            }
            //If the key is a number
            else if( ( event_h.key.keysym.unicode >= (Uint16)'0' ) && ( event_h.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                str += (char)event_h.key.keysym.unicode;
            }
            //If the key is a uppercase letter
            else if( ( event_h.key.keysym.unicode >= (Uint16)'A' ) && ( event_h.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                str += (char)event_h.key.keysym.unicode;
            }
            //If the key is a lowercase letter
            else if( ( event_h.key.keysym.unicode >= (Uint16)'a' ) && ( event_h.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                str += (char)event_h.key.keysym.unicode;
            }
        }

        //If backspace was pressed and the string isn't blank
        if( ( event_h.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
        {
            //Remove a character from the end
            str.erase( str.length() - 1 );
        }

        //If the string was changed
        if( str != temp )
        {
            //Free the old surface
            SDL_FreeSurface( text );

            //Render a new text surface
            strcpy(abv,str.c_str());
	    text = TTF_RenderText_Solid( font, str.c_str(), textColor );

        }
    }
}


void StringInput::show_centered() //prints cursor
{
    //If the surface isn't blank
    if( text != NULL)
    {
        //Show the name
        apply_surface(30,264 , text, screen );
        k=str.length();
        im = load_image( "images/cursor.bmp" );


    }
    apply_surface(30+(k*15),260, im, screen );
}


bool name_handle() //checks for keyboard inputs when name is being typed
{
	bool quit = false;
	bool nameEntered = false;
	StringInput name;
	font = TTF_OpenFont( "coders_crux.ttf", 40 );
	while( quit == false )
	{
		//While there's events to handle
		while( SDL_PollEvent( &event_h ) )
		{
			//If the user hasn't entered their name yet
			if( nameEntered == false )
			{
				//Get user input
				name.handle_input();

				//If the enter key was pressed
				if( ( event_h.type == SDL_KEYDOWN ) && ( event_h.key.keysym.sym == SDLK_RETURN ) )
				{
					//user entered the name
					nameEntered = true;
					return true;
				}
			}

			//If the user has Xed out the window
			if( event_h.type == SDL_QUIT )
			{
				//Quit the progrham
					quit = true;
					exit(0);
			}

			//Show the message
			im = load_image( "images/welcome.bmp" ); // screen for getting name
			apply_surface( 0, 0, im, screen );
			//to restore after evry keystroke..
			im = load_image( "images/cursor.bmp" ); //cursor image

			//Show the name on the screen
			name.show_centered();

			//Update the screen
			if( SDL_Flip( screen ) == -1 )
			{
			    return 1;
			}
		}
     }
	 return 4;
}


//basic function loads an image whose address is passed
SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    //Load the image using SDL_image
    loadedImage = IMG_Load( filename.c_str() );
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}


//applies any image to surface
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Rectangle to hold the offsets
    SDL_Rect offset;
    //Get offsets
    offset.x = x;
    offset.y = y;
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

//initiates SDL ...everything gets triggered
bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }
    if( TTF_Init() == -1 )
    {
    	exit(0);
        return false;
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
    	 return false;
    }
    //Set the window caption
    SDL_WM_SetCaption( "Smelly-Snake", NULL );
    //loading sound effects
    click = Mix_LoadWAV( "click.wav" );
    return true;
}


//cleans some of abhishek's stuff
void clean_up()
{
    //Free the surface
    SDL_FreeSurface( cover );
    Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();
}


//the function through which u enter gaming zone
//Its the "main" function...Backbone!!
bool play()
{
	int x,y;
	bool quit_play;

	im = load_image( "images/welcome.bmp" );
	apply_surface( 0, 0, im, screen );
	SDL_Flip( screen );
	name_handle();

	im = load_image( "images/back_before.bmp" );
	apply_surface( 204, 437, im, screen );
	im = load_image( "images/next_before.bmp" );
	apply_surface( 316, 437, im, screen );
	SDL_Flip( screen );
	while( quit_play== false )
	{

		//While there's an event to handle
		while( SDL_PollEvent( &event_p ) )
		{
			//If the user has Xed out the window
			if( event_p.type == SDL_QUIT )
			{
				quit_play=true;
				exit(0);
			}
			if( event_p.type == SDL_MOUSEBUTTONDOWN )
			{
				//If the left mouse button was pressed
				if( event_p.button.button == SDL_BUTTON_LEFT )
				{
					x = event_p.button.x;
					y = event_p.button.y;
					if( ( x > 204 ) && ( x < 291 ) && ( y > 437 ) && ( y < 469 ) )
					{
						im = load_image( "images/back_after.bmp" );
						apply_surface( 204, 437, im, screen );
						SDL_Flip( screen );
					}
					if( ( x > 316 ) && ( x < 403 ) && ( y > 437 ) && ( y < 469 ) )
					{
						im = load_image( "images/next_after.bmp" );
						apply_surface( 316, 437, im, screen );
						SDL_Flip( screen );
					}
				}
			}
			if( event_p.type == SDL_MOUSEBUTTONUP )
			{
				//If the left mouse button was released
				if( event_p.button.button == SDL_BUTTON_LEFT )
				{
					//Get the mouse offsets
					x = event_p.button.x;
					y = event_p.button.y;

					//If the mouse is over the button
					if( ( x > 204 ) && ( x < 291 ) && ( y > 437 ) && ( y < 469 ) )
					{

						return true;

					}

					if( ( x > 316 ) && ( x < 403 ) && ( y > 437 ) && ( y < 469 ) )
					{

					while( quit_play == false )
						{

							//While there's an event to handle
							while( SDL_PollEvent( &event_p ) )
							{
								main_himanshu();//this calls the part-II
								//If the user has Xed out the window
								if( event_p.type == SDL_QUIT )
								{
									//Quit the program
									quit_play = true;
									exit(0);
								}
							}
						}
						return true;

					}//end of play --> screen proceed to next

				}
				//to restore after click released
					//im = load_image( "images/welcome.bmp" );
					//apply_surface( 0, 0, im, screen );
					im = load_image( "images/back_before.bmp" );
					apply_surface( 204, 437, im, screen );
					im = load_image( "images/next_before.bmp" );
					apply_surface( 316, 437, im, screen );
					SDL_Flip( screen );

			}

		}
	}
	return true;
}

//just prints out controls and intructions
bool controls()
{
	int x,y;
	bool quit_control =false;
	im = load_image( "images/controls.bmp" );
	apply_surface( 0, 0, im, screen );
	SDL_Flip( screen );
	while( quit_control == false )
	{

		//While there's an event to handle
		while( SDL_PollEvent( &event_c ) )
		{

			if( event_c.type == SDL_QUIT )
			{
				//Quit the program
				quit_control = true;
				exit(0);
			}
			if( event_c.type == SDL_MOUSEBUTTONDOWN )
			{
				//If the left mouse button was pressed
				if( event_c.button.button == SDL_BUTTON_LEFT )
				{
					x = event_c.button.x;
					y = event_c.button.y;
					if( ( x > 538 ) && ( x < 624 ) && ( y > 441 ) && ( y < 474 ) )
					{
						im = load_image( "images/controls1.bmp" );
						apply_surface( 0, 0, im, screen );
						SDL_Flip( screen );
					}
				}
			}
			if( event_c.type == SDL_MOUSEBUTTONUP )
			{
				//If the left mouse button was released
				if( event_c.button.button == SDL_BUTTON_LEFT )
				{
					//Get the mouse offsets
					x = event_c.button.x;
					y = event_c.button.y;

					//If the mouse is over the button
					if( ( x > 538 ) && ( x < 624 ) && ( y > 441 ) && ( y < 474 ) )
					{
						return true;
					}
				}

				//to restore after click released
					im = load_image( "images/controls.bmp" );
					apply_surface( 0, 0, im, screen );
					SDL_Flip( screen );

			}
		}
	}
}

//this function is called by main().
//prints play, controls .records mouse events for the main screen
void mouse_events()
{
    //The mouse offsets
    int x = 0, y = 0;

    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION &&f==0)
    {

        //Get the mouse offsets
        if(f==79)
        {
            //do nothing
        }

	//Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        //If the mouse is over the button
        if( ( x > 300 ) && ( x < 472 ) && ( y >320 ) && ( y < 360 ) )
        {
            //image OVER
            button = load_image( "images/play_button1.bmp" );
            apply_surface( 300, 320, button, screen );
            SDL_Flip( screen );
	}
        //If not
        else
        {
            //Set the button sprite
            button = load_image( "images/play_button.bmp" );
            apply_surface( 300, 320, button, screen );
            SDL_Flip( screen );
        }
        if( ( x > 300 ) && ( x < 472 ) && ( y >376 ) && ( y < 416 ) )
        {
            //image OVER
            button = load_image( "images/controls_button1.bmp" );
            apply_surface( 300, 376, button, screen );
            SDL_Flip( screen );
        }
        //If not
        else
        {
            //Set the button sprite
            button = load_image( "images/controls_button.bmp" );
            apply_surface( 300, 376, button, screen );
            SDL_Flip( screen );
        }
    }
    label:
    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
		if( ( x > 300 ) && ( x < 472 ) && ( y >320 ) && ( y < 360 ) )
		{
			f=1;
			cover = load_image( "images/cover.bmp" );
			apply_surface( 0, 0, cover, screen );
			button = load_image( "images/controls_button.bmp" );
			apply_surface( 300, 376, button, screen );
		        button = load_image( "images/play_button1.bmp" );
			apply_surface( 305, 325, button, screen );
			SDL_Flip( screen );
		}
		else
		{

			button = load_image( "images/play_button.bmp" );
			apply_surface( 300, 320, button, screen );
			SDL_Flip( screen );
		}
		if( ( x > 300 ) && ( x < 472 ) && ( y >376 ) && ( y < 416 ) )
		{
			f=1;
			cover = load_image( "images/cover.bmp" );
			apply_surface( 0, 0, cover, screen );
			button = load_image( "images/play_button.bmp" );
			apply_surface( 300, 320, button, screen );
			button = load_image( "images/controls_button1.bmp" );
			apply_surface( 305, 381, button, screen );
			SDL_Flip( screen );
		}
		//If not
		else
		{
			//Set the button sprite
			button = load_image( "images/controls_button.bmp" );
			apply_surface( 300, 376, button, screen );
			SDL_Flip( screen );
		}
        }
    }
    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {

        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        {
	    f=0;
            //this is done to ensure that when button becomes up from down then cover is restored with black buttons
            cover = load_image( "images/cover.bmp" );
            apply_surface( 0, 0, cover, screen );
            button = load_image( "images/play_button.bmp" );
            apply_surface( 300, 320, button, screen );
            button = load_image( "images/controls_button.bmp" );
            apply_surface( 300, 376, button, screen );
            SDL_Flip( screen );
            x = event.button.x;
            y = event.button.y;

            //If the moue is over the button
            if( ( x > 300 ) && ( x < 472 ) && ( y >320 ) && ( y < 360 ) )
            {
            	Mix_PlayChannel( -1, click, 0);
                play();
            	cover = load_image( "images/cover.bmp" );
		apply_surface( 0, 0, cover, screen );
		button = load_image( "images/play_button.bmp" );
		apply_surface( 300, 320, button, screen );
		button = load_image( "images/controls_button.bmp" );
		apply_surface( 300, 376, button, screen );
		SDL_Flip( screen );
            }
            if( ( x > 300 ) && ( x < 472 ) && ( y >376 ) && ( y < 416 ) )
            {
            	Mix_PlayChannel( -1, click, 0 );
            	controls();
            	cover = load_image( "images/cover.bmp" );
		apply_surface( 0, 0, cover, screen );
		button = load_image( "images/play_button.bmp" );
		apply_surface( 300, 320, button, screen );
		button = load_image( "images/controls_button.bmp" );
		apply_surface( 300, 376, button, screen );
		SDL_Flip( screen );

            }

        }
    }
}

//function prints cover image..Snake wali
bool cover_func()
{
	f=0;
	bool quit;
	cover = load_image( "images/cover.bmp" );
	if( cover == NULL )
	{
		return 1;
	}
	//cover = load_image( "images/cover.bmp" );
	apply_surface( 0, 0, cover, screen );
	button = load_image( "images/play_button.bmp" );
	apply_surface( 300, 320, button, screen );
	button = load_image( "images/controls_button.bmp" );
	apply_surface( 300, 376, button, screen );
	//Update the screen
	if( SDL_Flip( screen ) == -1 )
	{
		return 1;
	}
	//SDL_Delay( 4000 );
	while( quit == false )
	{

		//While there's an event to handle
		while( SDL_PollEvent( &event ) )
		{

			mouse_events();
			//If the user has Xed out the window
			if( event.type == SDL_QUIT )
			{
				//Quit the program
				exit(0);
			}
		}
	}
	return true;
}



int main( int argc, char* args[] )
{
	int flag=0;
	if( init() == false )
	{
		return 1;
	}
	if(cover_func() == false)
	{
		return 2;
	}
	return 0;
}


//code - part II himanshu and ashish
//a& b store snake co-ords,ltx,y: lost tail, o1,o2:obstacles

void imgload(int level)
{
    switch(level)
    {
        case 1:     headu=SDL_LoadBMP("images/headu1.bmp");
                    headd=SDL_LoadBMP("images/headd1.bmp");
                    headl=SDL_LoadBMP("images/headl1.bmp");
                    headr=SDL_LoadBMP("images/headr1.bmp");
                    bodyu=SDL_LoadBMP("images/bodyu1.bmp");
                    bodyl=SDL_LoadBMP("images/bodyl1.bmp");
                    tailu=SDL_LoadBMP("images/tailu1.bmp");
                    tailr=SDL_LoadBMP("images/tailr1.bmp");
                    taill=SDL_LoadBMP("images/taill1.bmp");
                    taild=SDL_LoadBMP("images/taild1.bmp");
                    bendul=SDL_LoadBMP("images/bendul1.bmp");
                    bendur=SDL_LoadBMP("images/bendur1.bmp");
                    benddl=SDL_LoadBMP("images/benddl1.bmp");
                    benddr=SDL_LoadBMP("images/benddr1.bmp");break;

        case 2:     headu=SDL_LoadBMP("images/headu2.bmp");
                    headd=SDL_LoadBMP("images/headd2.bmp");
                    headl=SDL_LoadBMP("images/headl2.bmp");
                    headr=SDL_LoadBMP("images/headr2.bmp");
                    bodyu=SDL_LoadBMP("images/bodyu2.bmp");
                    bodyl=SDL_LoadBMP("images/bodyl2.bmp");
                    tailu=SDL_LoadBMP("images/tailu2.bmp");
                    tailr=SDL_LoadBMP("images/tailr2.bmp");
                    taill=SDL_LoadBMP("images/taill2.bmp");
                    taild=SDL_LoadBMP("images/taild2.bmp");
                    bendul=SDL_LoadBMP("images/bendul2.bmp");
                    bendur=SDL_LoadBMP("images/bendur2.bmp");
                    benddl=SDL_LoadBMP("images/benddl2.bmp");
                    benddr=SDL_LoadBMP("images/benddr2.bmp");break;

        case 3:     headu=SDL_LoadBMP("images/headu3.bmp");
                    headd=SDL_LoadBMP("images/headd3.bmp");
                    headl=SDL_LoadBMP("images/headl3.bmp");
                    headr=SDL_LoadBMP("images/headr3.bmp");
                    bodyu=SDL_LoadBMP("images/bodyu3.bmp");
                    bodyl=SDL_LoadBMP("images/bodyl3.bmp");
                    tailu=SDL_LoadBMP("images/tailu3.bmp");
                    tailr=SDL_LoadBMP("images/tailr3.bmp");
                    taill=SDL_LoadBMP("images/taill3.bmp");
                    taild=SDL_LoadBMP("images/taild3.bmp");
                    bendul=SDL_LoadBMP("images/bendul3.bmp");
                    bendur=SDL_LoadBMP("images/bendur3.bmp");
                    benddl=SDL_LoadBMP("images/benddl3.bmp");
                    benddr=SDL_LoadBMP("images/benddr3.bmp");break;

        case 4:     headu=SDL_LoadBMP("images/headu4.bmp");
                    headd=SDL_LoadBMP("images/headd4.bmp");
                    headl=SDL_LoadBMP("images/headl4.bmp");
                    headr=SDL_LoadBMP("images/headr4.bmp");
                    bodyu=SDL_LoadBMP("images/bodyu4.bmp");
                    bodyl=SDL_LoadBMP("images/bodyl4.bmp");
                    tailu=SDL_LoadBMP("images/tailu4.bmp");
                    tailr=SDL_LoadBMP("images/tailr4.bmp");
                    taill=SDL_LoadBMP("images/taill4.bmp");
                    taild=SDL_LoadBMP("images/taild4.bmp");
                    bendul=SDL_LoadBMP("images/bendul4.bmp");
                    bendur=SDL_LoadBMP("images/bendur4.bmp");
                    benddl=SDL_LoadBMP("images/benddl4.bmp");
                    benddr=SDL_LoadBMP("images/benddr4.bmp");break;

        case 5:     headu=SDL_LoadBMP("images/headu5.bmp");
                    headd=SDL_LoadBMP("images/headd5.bmp");
                    headl=SDL_LoadBMP("images/headl5.bmp");
                    headr=SDL_LoadBMP("images/headr5.bmp");
                    bodyu=SDL_LoadBMP("images/bodyu5.bmp");
                    bodyl=SDL_LoadBMP("images/bodyl5.bmp");
                    tailu=SDL_LoadBMP("images/tailu5.bmp");
                    tailr=SDL_LoadBMP("images/tailr5.bmp");
                    taill=SDL_LoadBMP("images/taill5.bmp");
                    taild=SDL_LoadBMP("images/taild5.bmp");
                    bendul=SDL_LoadBMP("images/bendul5.bmp");
                    bendur=SDL_LoadBMP("images/bendur5.bmp");
                    benddl=SDL_LoadBMP("images/benddl5.bmp");
                    benddr=SDL_LoadBMP("images/benddr5.bmp");break;

        case 6:     headu=SDL_LoadBMP("images/headu6.bmp");
                    headd=SDL_LoadBMP("images/headd6.bmp");
                    headl=SDL_LoadBMP("images/headl6.bmp");
                    headr=SDL_LoadBMP("images/headr6.bmp");
                    bodyu=SDL_LoadBMP("images/bodyu6.bmp");
                    bodyl=SDL_LoadBMP("images/bodyl6.bmp");
                    tailu=SDL_LoadBMP("images/tailu6.bmp");
                    tailr=SDL_LoadBMP("images/tailr6.bmp");
                    taill=SDL_LoadBMP("images/taill6.bmp");
                    taild=SDL_LoadBMP("images/taild6.bmp");
                    bendul=SDL_LoadBMP("images/bendul6.bmp");
                    bendur=SDL_LoadBMP("images/bendur6.bmp");
                    benddl=SDL_LoadBMP("images/benddl6.bmp");
                    benddr=SDL_LoadBMP("images/benddr6.bmp");break;

        case 7:     headu=SDL_LoadBMP("images/headu7.bmp");
                    headd=SDL_LoadBMP("images/headd7.bmp");
                    headl=SDL_LoadBMP("images/headl7.bmp");
                    headr=SDL_LoadBMP("images/headr7.bmp");
                    bodyu=SDL_LoadBMP("images/bodyu7.bmp");
                    bodyl=SDL_LoadBMP("images/bodyl7.bmp");
                    tailu=SDL_LoadBMP("images/tailu7.bmp");
                    tailr=SDL_LoadBMP("images/tailr7.bmp");
                    taill=SDL_LoadBMP("images/taill7.bmp");
                    taild=SDL_LoadBMP("images/taild7.bmp");
                    bendul=SDL_LoadBMP("images/bendul7.bmp");
                    bendur=SDL_LoadBMP("images/bendur7.bmp");
                    benddl=SDL_LoadBMP("images/benddl7.bmp");
                    benddr=SDL_LoadBMP("images/benddr7.bmp");break;

    }

    b1=SDL_LoadBMP("images/b1.bmp");
    f1=SDL_LoadBMP("images/f1.bmp");
    bf1=SDL_LoadBMP("images/bf1.bmp");
    clear=SDL_LoadBMP("images/clear.bmp");
    clear2=SDL_LoadBMP("images/clear2.bmp");
    font = TTF_OpenFont( "cont.TTF", 18 );
    tail=tailr;
    head=headr;

    SDL_EnableUNICODE( SDL_ENABLE );
}
void brickstore(int level)
{
    int i;
    tb=tb2=-1;
    if(level==2)
    {
        for(i=S;i<=MX-2*S;i+=S)
        {
        o1[++tb]=i;
        o2[++tb2]=2*S;
        }
        for(i=S;i<=MX-2*S;i+=S)
        {
        o1[++tb]=i;
        o2[++tb2]=MY-2*S;
        }
        for(i=2*S;i<=MY-2*S;i+=S)
        {
        o1[++tb]=S;
        o2[++tb2]=i;
        }
        for(i=2*S;i<=MY-2*S;i+=S)
        {
        o1[++tb]=MX-2*S;
        o2[++tb2]=i;
        }
    }

    else if(level==3)
    {
        for(i=S;i<=8*S;i+=S)//left horizon
        {
        o1[++tb]=i;
        o2[++tb2]=2*S;
        }
        for(i=S;i<=8*S;i+=S)
        {
        o1[++tb]=i;
        o2[++tb2]=MY-2*S;
        }
        for(i=MX-9*S;i<=MX-2*S;i+=S)//right horizon
        {
        o1[++tb]=i;
        o2[++tb2]=2*S;
        }
        for(i=MX-9*S;i<=MX-2*S;i+=S)
        {
        o1[++tb]=i;
        o2[++tb2]=MY-2*S;
        }
        for(i=2*S;i<=9*S;i+=S)//upper vertical
        {
        o1[++tb]=S;
        o2[++tb2]=i;
        }
        for(i=2*S;i<=9*S;i+=S)
        {
        o1[++tb]=MX-2*S;
        o2[++tb2]=i;
        }
        for(i=MY-9*S;i<=MY-2*S;i+=S)  //lower vertical
        {
        o1[++tb]=S;
        o2[++tb2]=i;
        }
        for(i=MY-9*S;i<=MY-2*S;i+=S)
        {
        o1[++tb]=MX-2*S;
        o2[++tb2]=i;
        }
        for(i=13*S;i<=26*S;i+=S)  //middle upper
        {
        o1[++tb]=i;
        o2[++tb2]=13*S;
        }
        for(i=13*S;i<=26*S;i+=S)// middle lower
        {
        o1[++tb]=i;
        o2[++tb2]=17*S;
        }
    }
    else if(level==4)
    {
        for(i=2*S;i<=20*S;i+=S)//upper vertical
        {
        o1[++tb]=10*S;
        o2[++tb2]=i;
        }
        for(i=11*S;i<=MY-2*S;i+=S) // lower vertical
        {
        o1[++tb]=MX-11*S;
        o2[++tb2]=i;
        }
        for(i=S;i<=13*S;i+=S)//lower horizon
        {
        o1[++tb]=i;
        o2[++tb2]=25*S;
        }
        for(i=MX-14*S;i<=MX-2*S;i+=S)//upper horizon
        {
        o1[++tb]=i;
        o2[++tb2]=6*S;
        }

    }
    else if(level==5)
    {
        for(i=S;i<=MX-2*S;i+=S)//upper horizon
        {
        o1[++tb]=i;
        o2[++tb2]=2*S;
        }
        for(i=S;i<=MX-2*S;i+=S) //lower horizon
        {
        o1[++tb]=i;
        o2[++tb2]=MY-2*S;
        }
        for(i=2*S;i<=9*S;i+=S)//upper vertical
        {
        o1[++tb]=S;
        o2[++tb2]=i;
        }
        for(i=2*S;i<=9*S;i+=S)
        {
        o1[++tb]=MX-2*S;
        o2[++tb2]=i;
        }
        for(i=MY-9*S;i<=MY-2*S;i+=S)  //lower vertical
        {
        o1[++tb]=S;
        o2[++tb2]=i;
        }
        for(i=MY-9*S;i<=MY-2*S;i+=S)
        {
        o1[++tb]=MX-2*S;
        o2[++tb2]=i;
        }
        for(i=13*S;i<=26*S;i+=S)  //middle upper
        {
        o1[++tb]=i;
        o2[++tb2]=10*S;
        }
        for(i=13*S;i<=27*S;i+=S)// middle lower
        {
        o1[++tb]=i;
        o2[++tb2]=20*S;
        }

    }
    else if(level==6)
    {
        for(i=S;i<=17*S;i+=S)  //middle upper 1
        {
        o1[++tb]=i;
        o2[++tb2]=13*S;
        }
        for(i=21*S;i<=MX-2*S;i+=S)  //middle upper 2
        {
        o1[++tb]=i;
        o2[++tb2]=13*S;
        }
        for(i=S;i<=MX-2*S;i+=S)// middle lower
        {
        o1[++tb]=i;
        o2[++tb2]=17*S;
        }
        for(i=17*S;i<=MY-2*S;i+=S)// lower vertical
        {
        o1[++tb]=21*S;
        o2[++tb2]=i;
        }
        for(i=S;i<=4*S;i+=S)//left horizon
        {
        o1[++tb]=i;
        o2[++tb2]=2*S;
        }
        for(i=2*S;i<=9*S;i+=S)//upper vertical
        {
        o1[++tb]=S;
        o2[++tb2]=i;
        }
        for(i=9*S;i<=30*S;i+=S)//right horizon
        {
        o1[++tb]=i;
        o2[++tb2]=2*S;
        }
    }
    else if(level==7)
    {
        for(i=15*S;i<=25*S;i+=S)  //middle upper 1
        {
        o1[++tb]=i;
        o2[++tb2]=5*S;
        }
        for(i=10*S;i<=30*S;i+=S)  //middle upper 2
        {
        o1[++tb]=i;
        o2[++tb2]=10*S;
        }
        for(i=S;i<=MX-2*S;i+=S)// middle lower
        {
        o1[++tb]=i;
        o2[++tb2]=17*S;
        }
        for(i=10*S;i<=30*S;i+=S)  //middle lower 2
        {
        o1[++tb]=i;
        o2[++tb2]=25*S;
        }
        for(i=17*S;i<=MY-2*S;i+=S)// lower vertical
        {
        o1[++tb]=21*S;
        o2[++tb2]=i;
        }
        for(i=S;i<=4*S;i+=S)//left horizon
        {
        o1[++tb]=i;
        o2[++tb2]=2*S;
        }
        for(i=2*S;i<=9*S;i+=S)//upper vertical
        {
        o1[++tb]=S;
        o2[++tb2]=i;
        }
        for(i=9*S;i<=30*S;i+=S)//right horizon
        {
        o1[++tb]=i;
        o2[++tb2]=2*S;
        }
    }


}
void printbrick()
{
     SDL_Rect offset;
     int i;

        for(i=0;i<=tb;i++)
        {
            offset.x=o1[i];
            offset.y=o2[i];

        SDL_BlitSurface(b1,NULL,screen,&offset);
        }
}
void printscore(int score)
{
            std::stringstream sscore;
            SDL_Rect offset;

            sscore<<"Score : "<<score;
            offset.x=500;
            offset.y=0;
            SDL_BlitSurface(clear2,NULL,screen,&offset);
            welcome = TTF_RenderText_Solid( font, sscore.str().c_str(), textColor );
            offset.x=500;
            offset.y=8;

            SDL_BlitSurface(welcome,NULL,screen,&offset);
}
void afterpause(int score)
{
    SDL_Rect offset;

    printbrick();// print bricks
    offset.x=p; offset.y=q;
    SDL_BlitSurface(f1,NULL,screen,&offset);// fruit
    printscore(score);//score
    //score tab //background //timer stop
    if(p1==0 && q1==0)
    {

    }
    else
    {
        offset.x=p1; offset.y=q1;
        SDL_BlitSurface(bf1,NULL,screen,&offset);// bfruit
    }
    SDL_Flip(screen);
}
void newlevel(int level=1,int score=0)//default level =1 and score =0, req wen this functon is called fromm main
{
    SDL_Rect offset;
    if(level==8)
    {
        SDL_FillRect(screen,NULL, 0x000000);/* equivalent to clear screen*/
                    offset.x=100; offset.y=225;
                    std::stringstream sscore;
                    sscore<<"WELL Played, Your Score: "<<score<<" Hit Enter To Exit";
                    welcome = TTF_RenderText_Solid( font, sscore.str().c_str(), textColor );
                    SDL_BlitSurface(welcome,NULL,screen,&offset);

                    std::stringstream sscore_name;
                    offset.x=100; offset.y=200;
                    sscore_name<< abv;
                    welcome = TTF_RenderText_Solid( font, sscore_name.str().c_str(), textColor );
                    SDL_BlitSurface(welcome,NULL,screen,&offset);

                    SDL_Flip(screen);
                    quit=false;
                    while(quit==false)/* waits for user to press return*/
                                    {
                                        if(SDL_PollEvent(&event))
                                        {
                                            if(event.type== SDL_KEYDOWN)
                                            switch( event.key.keysym.sym )
                                            {
                                                case SDLK_RETURN: quit=true;break;
                                                default:break;
                                            }
                                        }
                                    }
        quit=true;
        goto exit;
    }
    imgload(level);
    brickstore(level);
    quit = false;
    running=false;
    t=t2=-1;
    p1=q1=0;
    fruits=bfruits=0;// no. of fruits eaten
    quit=wel(level);
    if(quit== true)
    goto exit;
    basic(score);
    quit= mane();
   exit: if(quit== true)
    {
        SDL_FreeSurface(welcome);
    SDL_FreeSurface(headu);
    SDL_FreeSurface(headd);
    SDL_FreeSurface(headl);
    SDL_FreeSurface(headr);
    SDL_FreeSurface(bodyu);
    SDL_FreeSurface(bodyl);
    SDL_FreeSurface(tailu);
    SDL_FreeSurface(taild);
    SDL_FreeSurface(taill);
    SDL_FreeSurface(tailr);
    SDL_FreeSurface(head);
    SDL_FreeSurface(body);
    SDL_FreeSurface(tail);
    SDL_FreeSurface(bendul);
    SDL_FreeSurface(bendur);
    SDL_FreeSurface(benddl);
    SDL_FreeSurface(benddr);
    SDL_FreeSurface(b1);
    SDL_FreeSurface(f1);
    SDL_FreeSurface(bf1);
    SDL_FreeSurface(clear);
    SDL_FreeSurface(clear2);
    TTF_CloseFont( font );
    SDL_EnableUNICODE( SDL_DISABLE );
    //Quit SDL
    SDL_Quit();
    }

}


//int main( int argc, char* args[] )
int main_himanshu()
{
    newlevel();
    SDL_FreeSurface(welcome);
    SDL_FreeSurface(headu);
    SDL_FreeSurface(headd);
    SDL_FreeSurface(headl);
    SDL_FreeSurface(headr);
    SDL_FreeSurface(bodyu);
    SDL_FreeSurface(bodyl);
    SDL_FreeSurface(tailu);
    SDL_FreeSurface(taild);
    SDL_FreeSurface(taill);
    SDL_FreeSurface(tailr);
    SDL_FreeSurface(head);
    SDL_FreeSurface(body);
    SDL_FreeSurface(tail);
    SDL_FreeSurface(bendul);
    SDL_FreeSurface(bendur);
    SDL_FreeSurface(benddl);
    SDL_FreeSurface(benddr);
    SDL_FreeSurface(b1);
    SDL_FreeSurface(f1);
    SDL_FreeSurface(bf1);
    SDL_FreeSurface(clear);
    SDL_FreeSurface(clear2);
    TTF_CloseFont( font );
    SDL_EnableUNICODE( SDL_DISABLE );
    //Quit SDL
    SDL_Quit();

    return 0;
}

bool wel(int level)
{
    SDL_Rect offset;/* coordinates of the welcome message*/
    offset.x=100;
    offset.y=225;

    SDL_Rect start;/* coordinates of the starting point of snake*/
    start.x=3*S;
    start.y=26*S;

    /* prints welcome message*/
    switch(level)
    {
        case 1:welcome = TTF_RenderText_Solid( font, "Level 1, Hit Enter to Enjoy, Press P to pause or resume", textColor );break;
        case 2:welcome = TTF_RenderText_Solid( font, "Level 2, Hit Enter to Enjoy, Press P to pause or resume", textColor );break;
        case 3:welcome = TTF_RenderText_Solid( font, "Level 3, Hit Enter to Enjoy, Press P to pause or resume", textColor );break;
        case 4:welcome = TTF_RenderText_Solid( font, "Level 4, Hit Enter to Enjoy, Press P to pause or resume", textColor );break;
        case 5:welcome = TTF_RenderText_Solid( font, "Level 5, Hit Enter to Enjoy, Press P to pause or resume", textColor );break;
        case 6:welcome = TTF_RenderText_Solid( font, "Level 6, Hit Enter to Enjoy, Press P to pause or resume", textColor );break;
        case 7:welcome = TTF_RenderText_Solid( font, "Level 7, Hit Enter to Enjoy, Press P to pause or resume", textColor );break;
        default: break;
    }
    SDL_FillRect(screen,NULL, 0x000000);
    SDL_BlitSurface(welcome,NULL,screen,&offset);
    SDL_Flip(screen);
    while(quit==false)/* waits for user to press return*/
    {
        if(SDL_PollEvent(&event))
        {
            if( event.type == SDL_QUIT )/* if user hit red cross*/
            {quit = true;
            return quit;}
            else if(event.type== SDL_KEYDOWN)
            switch( event.key.keysym.sym )// why doesnt if work*** if . . .= _ *****
                {
                    case SDLK_RETURN: quit= true;break;
                    default: break;
                }
        }
    }
        SDL_FillRect(screen,NULL, 0x000000);/* equivalent to clear screen*/
        SDL_Flip(screen);

        SDL_BlitSurface(headr,NULL,screen,&start);// first snake is printed*/
        SDL_Flip(screen);
         a[++t]=start.x;
         b[++t2]=start.y;
         return false;// if enter is pressed return false
        //SDL_Delay(5000);

}

void basic(int score)
{
    int i;
    bool overlap=true;
    SDL_Rect offset;
    printbrick();

    offset.x=500;
    offset.y=8;

    /* prints score*/
    std::stringstream sscore;
    sscore<<"Score : "<<score;
    welcome = TTF_RenderText_Solid( font, sscore.str().c_str(), textColor );
    SDL_BlitSurface(welcome,NULL,screen,&offset);
    SDL_Flip(screen);

    /* printing our first fruit*/

    while(overlap==true)
    {
            offset.x=rand()%(MX-2*S-3*W)+S+W;/* also:srand(X) */
            offset.y=rand()%(MY-2*S-4*H)+S+2*H;
            /* making sure that order of 16 is maintained*/
            offset.x=offset.x-offset.x%16;
            offset.y=offset.y-offset.y%16;
            for(i=0;i<=tb;i++)
            if(offset.x==o1[i] && offset.y== o2[i])
            break;
            if(i>tb)
            overlap=false;
    }

            p=offset.x;/* storing fruit coords in universal variables for easy access in other functions*/
            q=offset.y;

        SDL_BlitSurface(f1,NULL,screen,&offset);/* fruit printed*/
        SDL_Flip(screen);
    //SDL_Delay(5000);
}

bool mane()
{
    bool quit=false,pause=true,overlap=true;
    int x=a[t],y=b[t],i=0,ptimer=0,ptimer1=0,ctop=-1;
    static int score=0,level=1;
    std::string cheats;
    SDL_Rect offset;
    char ch='r',ch1='r';
    while(quit==false)/* a loop that breaks only if snake hits boundary or bites itself or user clicks the red cross*/
    {
        while(SDL_PollEvent(&event))/* if there is an event to study*/
        {
            if( event.type == SDL_QUIT )/* if user hit red cross*/
            {quit = true;
            return quit;}
            else if(event.type== SDL_KEYDOWN)// or if user hit an arrow key
            {
                switch( event.key.keysym.sym )//
                {
                    case SDLK_UP: if(ch!='d')
                                   {ch1=ch;
                                   ch='u';}
                                   cheats.clear();break;
                    case SDLK_DOWN: if(ch!='u')
                                    {ch1=ch;
                                   ch='d';}
                                   cheats.clear();break;
                    case SDLK_LEFT: if(ch!='r')
                                    {ch1=ch;
                                   ch='l';}
                                   cheats.clear();break;
                    case SDLK_RIGHT: if(ch!='l')
                                      {ch1=ch;
                                   ch='r';}
                                   cheats.clear();break;
                    case SDLK_p:    SDL_FillRect(screen,NULL, 0x000000);/* equivalent to clear screen*/
                                    SDL_Flip(screen);
                                    cheats.clear();
                                    welcome = TTF_RenderText_Solid( font, "Hit P to Continue", textColor );
                                    offset.x=240; offset.y=220;
                                    SDL_BlitSurface(welcome,NULL,screen,&offset);
                                    SDL_Flip(screen);
                                    if(running==true)
                                    {
                                        ptimer1=ptimer;
                                        ptimer=SDL_GetTicks();// += if two breaks in same bfruit then also consider prev break
                                    }
                                    pause=true;
                                    while(pause==true)/* waits for user to press return*/
                                    {
                                        if(SDL_PollEvent(&event))
                                        {
                                            if(event.type== SDL_KEYDOWN)
                                            switch( event.key.keysym.sym )
                                            {
                                                case SDLK_p: pause= false;
                                                             SDL_FillRect(screen,NULL, 0x000000);/* equivalent to clear screen*/
                                                             SDL_Flip(screen);
                                                             afterpause(score);
                                                             if(running==true)
                                                             {
                                                                 ptimer=SDL_GetTicks()-ptimer;
                                                                 ptimer+=ptimer1;
                                                             }break;
                                                default: break;
                                            }
                                        }
                                    }break;
                    default:if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
                            {
                                //Append the character
                                cheats+= (char)event.key.keysym.unicode;
                            }
                            //If the key is a uppercase letter
                            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
                            {
                                //Append the character
                                cheats+= (char)event.key.keysym.unicode;
                            }
                            //If the key is a lowercase letter
                            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
                            {
                                //Append the character
                                cheats+= (char)event.key.keysym.unicode;
                            }

                             if(cheats=="accio")//case insensitive
                                {
                                    level++;
                                    levscore[++tlev]=score;
                                    cheats.clear();
                                    newlevel(level,score);
                                }
                            else if(cheats=="gemino")//case insensitive
                                {
                                    score+=5;
                                    cheats.clear();
                                    printscore(score);
                                    SDL_Flip(screen);
                                }
                }
            }
        }
        /*else// if there was no event to study
        {*/
            ltx=offset.x=a[0];// take snake's tail coordinates
            lty=offset.y=b[0];
            SDL_BlitSurface(clear,NULL,screen,&offset);/*clear only the tail*/
            SDL_Flip(screen);

            for(i=1; i<=t; i++)// shift the cooords in our arrays one step backwards as there is no need to--
            a[i-1]=a[i];       //--store the lost tail
            for(i=1; i<=t2; i++)
            b[i-1]=b[i];
            t--;
            t2--;

            if(ch=='l')// now add one more cordinate to compensate for the lost tail in the direction of
            {
                 x-=W;
                 if(x==-W)
                 x=MX-W;
            }

         // snake's movement
            else if(ch=='r')//this means one element lost in form of tail and other added before head
            {
                 x+=W;
                 if(x==MX)// portal
                 x=0;
            }          // that is the snake has moved
            else if(ch=='u')
            {
                 y-=H;
                 if(y==S)
                 y=MY-H;
            }
            else if(ch=='d')
            {
                 y+=H;
                 if(y==MY)
                 y=2*S;
            }
            a[++t]=x;// pushed the co-ords of the added part into the array
            b[++t2]=y;

            print(ch);// print the snake on screen

          if(t>=1)/* game over conditons are dealt */
        {
            for(i=0; i<t; i++)
            {
                if(a[t]==a[i]&&b[t]==b[i])/* if snake bit itself */
                {
                    SDL_FillRect(screen,NULL, 0x000000);/* equivalent to clear screen*/
                    offset.x=100; offset.y=225;

                    std::stringstream sscore;
                    sscore<<"WELL Played, Your Score: "<<score<<" Hit Enter To Exit";
                    welcome = TTF_RenderText_Solid( font, sscore.str().c_str(), textColor );
                    SDL_BlitSurface(welcome,NULL,screen,&offset);

                    std::stringstream sscore_name;
                    offset.x=100; offset.y=200;
                    sscore_name<< abv;
                    welcome = TTF_RenderText_Solid( font, sscore_name.str().c_str(), textColor );
                    SDL_BlitSurface(welcome,NULL,screen,&offset);
                    SDL_Flip(screen);

                    quit=false;
                    while(quit==false)/* waits for user to press return*/
                                    {
                                        if(SDL_PollEvent(&event))
                                        {
                                            if(event.type== SDL_KEYDOWN)
                                            switch( event.key.keysym.sym )
                                            {
                                                case SDLK_RETURN: quit=true;break;
                                                default:break;
                                            }
                                        }
                                    }

                    quit= true;
                    return quit;
                }
            }
        }
        if(level > 1)
        for(i=0;i<=tb;i++)// if snake hits boundary
        {
            if((a[t]>=o1[i] && a[t]<=o1[i]+15) && (b[t]>=o2[i] && b[t] <= o2[i]+15) )
            {

			SDL_FillRect(screen,NULL, 0x000000);/* equivalent to clear screen*/
                    offset.x=100; offset.y=225;
                    std::stringstream sscore;
                    sscore<<"WELL Played , Your Score: "<<score<<" Hit Enter To Exit";
                    welcome = TTF_RenderText_Solid( font, sscore.str().c_str(), textColor );
                    SDL_BlitSurface(welcome,NULL,screen,&offset);

                    std::stringstream sscore_name;
                    offset.x=100; offset.y=200;
                    sscore_name<< abv;
                    welcome = TTF_RenderText_Solid( font, sscore_name.str().c_str(), textColor );
                    SDL_BlitSurface(welcome,NULL,screen,&offset);


                    SDL_Flip(screen);
                    quit=false;
                    while(quit==false)/* waits for user to press return*/
                                    {
                                        if(SDL_PollEvent(&event))
                                        {
                                            if(event.type== SDL_KEYDOWN)
                                            switch( event.key.keysym.sym )
                                            {
                                                case SDLK_RETURN: quit=true;break;
                                                default:break;
                                            }
                                        }
                                    }

                    quit= true;
                    return quit;
            }
        }
        if(a[t]==p&&b[t2]==q)/* if fruit is eaten*/
        {
            if(ch=='l')  // x=a[t]
                x-=W;
            else if(ch=='r')
                x+=W;
            else if(ch=='u')
                y-=H;
            else if(ch=='d')
                y+=H;
            a[++t]=x;
            b[++t2]=y;

            score+=1;//// update the score
            fruits++;//update no. of fruits eaten
            if (fruits%5==0 && fruits!=0 && bfruits<=2)// generate bonus fruit
            {
                // generate new fruit
                overlap=true;
                while(overlap==true)
                {
                offset.x=rand()%(MX-2*S-3*W)+S+W;// also:srand(X)
                offset.y=rand()%(MY-2*S-4*H)+S+2*H;
                offset.x=offset.x-offset.x%16;
                offset.y=offset.y-offset.y%16;

                for(i=0;i<=tb;i++)
                if(offset.x==o1[i] && offset.y== o2[i])
                break;
                if(i>tb)
                overlap=false;
                }

                p1=offset.x;/* storing fruit coords in universal variables for easy access in other functions*/
                q1=offset.y;

                bfruits++;

                SDL_BlitSurface(bf1,NULL,screen,&offset);// bonus fruit printed
                running= true;
                start= SDL_GetTicks();

            }
            /* print the score*/
            printscore(score);
            SDL_Flip(screen);

            /* generate new fruit if 9 fruits are eaten(till 10th fruit)*/
            if(fruits<10)
               {
                    overlap=true;
                    while(overlap == true)
                    {
                    offset.x=rand()%(MX-2*S-3*W)+S+W;/* also:srand(X) */
                    offset.y=rand()%(MY-2*S-4*H)+S+2*H;
                    /* making sure that order of 16 is maintained*/
                    offset.x=offset.x-offset.x%16;
                    offset.y=offset.y-offset.y%16;

                     for(i=0;i<=tb;i++)
                    if(offset.x==o1[i] && offset.y== o2[i])
                    break;
                    if(i>tb)
                    overlap=false;
                    }

                    p=offset.x;/* pushed the co-ord of new food into universal variables*/
                    q=offset.y;

                    SDL_BlitSurface(f1,NULL,screen,&offset);// printed the new fruit on screen
               }
        SDL_Flip(screen);
        }

        // if timer should run
        {
            if(SDL_GetTicks()-start-ptimer>=T*1000 && running == true)
            {
                running=false;// stop timer and vlear timer and clear the  bonus fruit
                offset.x=p1;
                offset.y=q1;
                SDL_BlitSurface(clear,NULL,screen,&offset);
                offset.x=270;
                offset.y=0;
                SDL_BlitSurface(clear2,NULL,screen,&offset);
                if(bfruits==2 && fruits==10)// level advance condition 3
                {
                    level++;
                    levscore[++tlev]=score;
                    newlevel(level,score);
                }

            }
                else if(running== true)//update timer on screen
                {
                    offset.x=270;
                    offset.y=0;
                     SDL_BlitSurface(clear2,NULL,screen,&offset);

                    offset.x=270;
                    offset.y=8;
                    std::stringstream stimer;
                    stimer<<((T*1000-SDL_GetTicks()+start+ptimer)/1000);
                    welcome = TTF_RenderText_Solid( font, stimer.str().c_str(), textColor );
                    SDL_BlitSurface(welcome,NULL,screen,&offset);
                    SDL_Flip(screen);

                }
        }

        // if bonus fruit is eaten
        if(running== true && a[t]==p1 && b[t2]==q1)
        {
            score+= ((T*1000-SDL_GetTicks()+start+ptimer)/1000);
            printscore(score);

            running=false;
            ptimer=0;
            ptimer1=0;
            p1=0;// signify that the bonus fruit is dead
            q1=0;

            offset.x=270;
            offset.y=0;
            SDL_BlitSurface(clear2,NULL,screen,&offset);
            SDL_Flip(screen);

            if(bfruits==2 && fruits==10)// level advance condition 3
            {
                level++;
                newlevel(level,score);
            }
        }

        /*}*/
        SDL_Delay(100);
    }
  }

/* *** when i repaced the if condition of arrow keys with while the game improved significantly*** */

void print(char ch)
{
    int i;
    SDL_Rect offset;

    if(t!=0)
    {
        offset.x=a[0];/* print tail*/
        offset.y=b[0];
      /* now comparing tail with the lost tail*/
      if(offset.x==ltx-W)
      tail=taill;
      else if(offset.x==ltx+W)
      tail=tailr;
      else if(offset.y==lty-H)
      tail=tailu;
      else if(offset.y==lty+H)
      tail=taild;
      //change tail only with change of dir and else no need
      if((offset.y==b[1]+H && offset.x==ltx-W)|| (offset.y==b[1]+H && offset.x==ltx+W))
      tail=tailu;
      else if((offset.y==b[1]+H && offset.x==ltx+MX-W)|| (offset.y==b[1]+H && offset.x==ltx-MX+W) || (offset.y==b[1]-MY+2*S+H && offset.x==ltx+W)|| (offset.y==b[1]-MY+2*S+H && offset.x==ltx-W))//portal
      tail=tailu;
      else if((offset.y==b[1]-H && offset.x==ltx+W)|| (offset.y==b[1]-H && offset.x==ltx-W))
      tail=taild;
      else if((offset.y==b[1]-H && offset.x==ltx+MX-W)|| (offset.y==b[1]-H && offset.x==ltx-MX+W) || (offset.y==b[1]+MY-2*S-H && offset.x==ltx-W)|| (offset.y==b[1]+MY-2*S-H && offset.x==ltx+W))//portal
      tail=taild;
      else if((offset.x==a[1]-W && offset.y==lty-H)|| (offset.x==a[1]-W && offset.y==lty+H))
      tail=tailr;
      else if((offset.x==a[1]-W && offset.y==lty-MY+H+2*S)|| (offset.x==a[1]-W && offset.y==lty+MY-H-2*S) || (offset.x==a[1]+MX-W && offset.y==lty+H)|| (offset.x==a[1]+MX-W && offset.y==lty-H))//portal
      tail=tailr;
      else if((offset.x==a[1]+W && offset.y==lty-H)|| (offset.x==a[1]+W && offset.y==lty+H))
      tail=taill;
      else if((offset.x==a[1]+W && offset.y==lty-MY+H+2*S)|| (offset.x==a[1]+W && offset.y==lty+MY-H-2*S) || (offset.x==a[1]-MX+W && offset.y==lty+H)|| (offset.x==a[1]-MX+W && offset.y==lty-H))//portal
      tail=taill;

            SDL_BlitSurface(tail,NULL,screen,&offset);
    }

    for(i=1; i<t; i++)// now print the snake  body on screen from tail to head
          {
              offset.x=a[i];
              offset.y=b[i];

              if( offset.x==a[i-1]-W || offset.x==a[i-1]+W || offset.x==a[i+1]-W || offset.x==a[i+1]+W)
              body=bodyl;
              if( offset.y==b[i-1]-H || offset.y==b[i-1]+H || offset.y==b[i+1]+H || offset.y==b[i+1]-H)
              body=bodyu;
              if((offset.x==a[i+1]-W && offset.y==b[i-1]+H)||(offset.y==b[i+1]+H && offset.x==a[i-1]-W))//╚
              body= bendur;
              if((offset.x==a[i+1]-W && offset.y==b[i-1]-MY+2*S+H)||(offset.y==b[i+1]+H && offset.x==a[i-1]+MX-W) || (offset.x==a[i+1]+MX-W && offset.y==b[i-1]+H)||(offset.y==b[i+1]-MY+2*S+H && offset.x==a[i-1]-W))//╚portal
              body= bendur;
              if((offset.x==a[i+1]-W && offset.y==b[i-1]-H)|| (offset.y==b[i+1]-H && offset.x==a[i-1]-W) )//╔
              body= benddr;
              if((offset.x==a[i+1]-W && offset.y==b[i-1]+MY-2*S-H)|| (offset.y==b[i+1]-H && offset.x==a[i-1]+MX-W) || (offset.x==a[i+1]+MX-W && offset.y==b[i-1]-H)|| (offset.y==b[i+1]+MY-2*S-H && offset.x==a[i-1]-W))//╔portal
              body= benddr;
              if((offset.x==a[i+1]+W && offset.y==b[i-1]+H)||(offset.y==b[i+1]+H && offset.x==a[i-1]+W))//╝ i+1=>head & i-1=> tail
              body= bendul;
              if((offset.x==a[i+1]+W && offset.y==b[i-1]-MY+2*S+H)||(offset.y==b[i+1]+H && offset.x==a[i-1]-MX+W) || (offset.x==a[i+1]-MX+W && offset.y==b[i-1]+H)||(offset.y==b[i+1]-MY+2*S+H && offset.x==a[i-1]+W))//╝ i+1=>head & i-1=> tail
              body= bendul;//portal move snake inside the tunnel in comment twice in same and twice in opp dir.*
              if((offset.x==a[i+1]+W && offset.y==b[i-1]-H) ||(offset.y==b[i+1]-H && offset.x==a[i-1]+W))//╗-head down& tail left ir vice-versa
              body= benddl;
              if((offset.x==a[i+1]+W && offset.y==b[i-1]+MY-2*S-H) ||(offset.y==b[i+1]-H && offset.x==a[i-1]-MX+W) || (offset.x==a[i+1]-MX+W && offset.y==b[i-1]-H) ||(offset.y==b[i+1]+MY-2*S-H && offset.x==a[i-1]+W))//╗-head down& tail left ir vice-versa
              body= benddl;//portal


              SDL_BlitSurface(body,NULL,screen,&offset);
          }

    offset.x=a[t];/* print head*/
    offset.y=b[t];
    /* now comparing head with the lost previous head*/
    if(t>0)
    {
        if(offset.x==a[t-1]-W)
        head=headl;
        else if(offset.x==a[t-1]+W)
        head=headr;
        else if(offset.y==b[t-1]-H)
        head=headu;
        else if(offset.y==b[t-1]+H)
        head=headd;
    }
    else if(t==0)
    {
        if(ch=='l')
        head=headl;
        else if(ch=='r')
        head=headr;
        else if(ch=='u')
        head=headu;
        else if(ch=='d')
        head=headd;
    }

         SDL_BlitSurface(head,NULL,screen,&offset);

          SDL_Flip(screen);
}


