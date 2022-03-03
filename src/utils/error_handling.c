#include "error_handling.h"

void getErrorAndLog() {
   GLenum err = glGetError();
   if (err != GL_NO_ERROR) {
       printf("Error! Something is gravely wrong here.\n");
       printf("Error code: %d",err);
   } 
}