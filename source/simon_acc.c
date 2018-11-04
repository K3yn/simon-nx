#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SDL_helper.h"
#include "simon_acc.h"

void getUserInfo(){
    Result rc=0;
    u128 userID=0;
	void *buf;
	size_t len;
	
    bool account_selected=0;
    AccountProfile profile;
    AccountUserData userdata;
    AccountProfileBase profilebase;
    memset(&userdata, 0, sizeof(userdata));
    memset(&profilebase, 0, sizeof(profilebase));
	memset(&buf, 0, sizeof(buf));
	memset(&len, 0, sizeof(len));
    rc = accountInitialize();
    if (R_FAILED(rc)) {
		strcpy(errorAccount,"accountInitialize() failed:");
       // printf("accountInitialize() failed: 0x%x\n", rc);
    }

     if (R_SUCCEEDED(rc)) {
        // printf("Current userID: 0x%lx 0x%lx\n", (u64)(userID>>64), (u64)userID);
		rc = accountGetActiveUser(&userID, &account_selected);
        if (R_FAILED(rc)) {
           // printf("accountGetActiveUser() failed: 0x%x\n", rc);
        }
        else if(!account_selected) {
            //printf("No user is currently selected.\n");
			strcpy(errorAccount,"No user is currently selected.\n");
			userAnonymous=true;
            rc = -1;
        }	
		if (R_SUCCEEDED(rc)) {
			//strcpy(errorAccount,"Current userID:");
            rc = accountGetProfile(&profile, userID);
			//printf("Current userID: 0x%lx 0x%lx\n", (u64)(userID>>64), (u64)userID);
            if (R_FAILED(rc)) {
                //printf("accountGetProfile() failed: 0x%x\n", rc);
				strcpy(errorAccount,"accountGetProfile() failed:");
            }
        }

        if (R_SUCCEEDED(rc)) {
            rc = accountProfileGet(&profile, &userdata, &profilebase);//userdata is otional, see libnx acc.h.

            if (R_FAILED(rc)) {
                //printf(" 0x%x\n", rc);
				strcpy(errorAccount,"accountProfileGet() failed:");
            }

            if (R_SUCCEEDED(rc)) {
                memset(username,  0, sizeof(username));
                strncpy(username, profilebase.username, sizeof(username)-1);//Even though profilebase.username usually has a NUL-terminator, don't assume it does for safety.

               // printf("username: %s\n", username);//Note that the print-console doesn't support UTF-8. The username is UTF-8, so this will only display properly if there isn't any non-ASCII characters. To display it properly, a print method which supports UTF-8 should be used instead.
				u8* buffer;
				size_t image_size, real_size;
			   //You can also use accountProfileGetImageSize()/accountProfileLoadImage() to load the icon for use with a JPEG library, for displaying the user profile icon. See libnx acc.h.

			//load icon
       
			if (R_SUCCEEDED(accountProfileGetImageSize(&profile, &image_size)) &&
				(buffer = (u8*)malloc(image_size)) != NULL &&
				R_SUCCEEDED(accountProfileLoadImage(&profile, buffer, image_size, &real_size)))
			{
				SDL_LoadImage(&icon.texture, buffer, image_size);
				free(buffer);
			}

				}
				
				accountProfileClose(&profile);
			}

	 accountExit();
	}
}
