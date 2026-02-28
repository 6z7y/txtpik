#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BYTES 2048

// commands
#define WAYLAND_CMD   "grim -g \"$(slurp)\" /tmp/txtpik-cache.png"
#define X11_CMD       "maim -s -o /tmp/txtpik-cache.png"

#define TESSERACT_CMD "tesseract-ocr /tmp/txtpik-cache.png stdout 2>/dev/null"

// run tesseract-ocr
int get_output(char *buf)
{
  // Open a pipe to run Tesseract OCR and read its output
  FILE *pipe_cmd = popen(TESSERACT_CMD, "r");
  if (!pipe_cmd) { perror("Pipe open"); return -1; }

  buf[0] = '\0';        // initialize output buffer
  char line[MAX_BYTES]; // temporary buffer for each line

  // Read all lines from Tesseract stdout
  while(fgets(line, MAX_BYTES, pipe_cmd)) {

    // Append line if buffer has enough space, else stop
    if (strlen(buf) + strlen(line) + 1 < MAX_BYTES) 
        strcat(buf, line);

    else break;
  }

  pclose(pipe_cmd); // close pipe
  return 0;
}

int main()
{
  char buf[MAX_BYTES]; // store text
  buf[0] = '\0';       // initialize buffer to empty

  // 1. Detect display server type
  int is_wayland = ( !strcmp( getenv("XDG_SESSION_TYPE"), "wayland")) ? 1 : 0;

  // 2. Take screenshot using Wayland or X11
  if (is_wayland) system(WAYLAND_CMD);
  else            system(X11_CMD);

  // 3. Run OCR and get text output from screenshot
  if (get_output(buf) < 0) goto bye;

  // 4. Print recognized text
  printf("%s", buf);

  // 5. Remove temporary screenshot
  unlink("/tmp/txtpik-cache.png");

bye:
  return 0;
}
