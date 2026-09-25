#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unistd.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <gbm.h>
#include <xf86drmMode.h>

int main(int argc, char* argv[])
{
  const char* dri_device_group;
  const char* dri_device_group_default = "/dev/dri/card"; // getenv("DRI_DEVICE");
  char dri_device[300];
  int dri_fd;

  if (argc >= 2) {
    dri_device_group = argv[1];
  } else {
    dri_device_group = dri_device_group_default;
  }

  for (int i = 0; i < 4; i++) {
    sprintf(dri_device,"%s%d",dri_device_group,i);
    printf ("\nOpen DRI device %s ",dri_device);
    dri_fd = open(dri_device, O_RDWR);

    if (dri_fd == -1) {
      printf(" fail: %s\n",strerror(errno));
      continue;
    } else {
      printf (" OK\n");
    }

    printf(" .. create GBM device ");
    struct gbm_device *native_display = gbm_create_device(dri_fd);
    if (native_display == nullptr) {
	printf(" fail\n");
	continue;
      } else {
	printf (" OK\n");
      }

    printf(" .. drmModeGetResources() ");
    drmModeRes *resources = drmModeGetResources(dri_fd);
    if (resources == nullptr) {
      printf(" fail\n");
      continue;
    } else {
      printf (" OK\n");
    }
    close (dri_fd);
  }
}
