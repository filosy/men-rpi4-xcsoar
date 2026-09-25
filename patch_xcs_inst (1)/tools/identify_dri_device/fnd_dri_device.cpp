#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <gbm.h>
#include <xf86drmMode.h>

int main(int argc, char* argv[])
{
  const char* dri_device_group = "/dev/dri/card"; // getenv("DRI_DEVICE");
  char dri_device[30];
  int dri_fd;

  for (int i = 0; i < 2; i++) {
    sprintf(dri_device,"%s%d",dri_device_group,i);
    // printf ("opening %s ...",dri_device);
    dri_fd = open(dri_device, O_RDWR);
    // printf (" %d\n",dri_fd);

    if (dri_fd != -1) {
      drmModeRes *resources = drmModeGetResources(dri_fd);
      if (resources != nullptr) {
	printf("%s\n",dri_device);
	exit(EXIT_SUCCESS);
      }
    }
    close (dri_fd);
  }

  fprintf(stderr, "No usable DRI device found\n");
  exit(EXIT_FAILURE);
}
