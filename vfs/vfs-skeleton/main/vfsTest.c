/**
 * Test the Virtual File System
 *
 * Perform a test against the Virtual File System.
 *
 * For additional details and documentation see:
 * * Free book on ESP32 - https://leanpub.com/kolban-ESP32
 *
 *
 * Neil Kolban <kolban1@kolban.com>
 *
 */

#include <esp_vfs.h>
#include <esp_log.h>
#include <fcntl.h>
#include "vfsTest.h"
#include "sdkconfig.h"

static char tag[] = "vfsTest";

/**
 * Log the flags that are specified in an open() call.
 */
static void logFlags(int flags) {
	ESP_LOGD(tag, "flags:");
	if (flags & O_APPEND) {
		ESP_LOGD(tag, "- O_APPEND");
	}
	if (flags & O_CREAT) {
		ESP_LOGD(tag, "- O_CREAT");
	}
	if (flags & O_TRUNC) {
		ESP_LOGD(tag, "- O_TRUNC");
	}
	if (flags & O_RDONLY) {
		ESP_LOGD(tag, "- O_RDONLY");
	}
	if (flags & O_WRONLY) {
		ESP_LOGD(tag, "- O_WRONLY");
	}
	if (flags & O_RDWR) {
		ESP_LOGD(tag, "- O_RDWR");
	}
} // End of logFlags


static size_t vfs_write(int fd, const void *data, size_t size) {
	ESP_LOGI(tag, ">> write fd=%d, data=0x%lx, size=%d", fd, (unsigned long)data, size);
	return 0;
}


static off_t vfs_lseek(int fd, off_t offset, int whence) {
	ESP_LOGI(tag, ">> lseek fd=%d, offset=%d, whence=%d", fd, (int)offset, whence);
	return 0;
}


static ssize_t vfs_read(int fd, void *dst, size_t size) {
	ESP_LOGI(tag, ">> read fd=%d, dst=0x%lx, size=%d", fd, (unsigned long)dst, size);
	return 0;
}


/**
 * Open the file specified by path.  The flags contain the instructions
 * on how the file is to be opened.  For example:
 *
 * O_CREAT  - Create the named file.
 * O_TRUNC  - Truncate (empty) the file.
 * O_RDONLY - Open the file for reading only.
 * O_WRONLY - Open the file for writing only.
 * O_RDWR   - Open the file for reading and writing.
 *
 * The mode are access mode flags.
 */
static int vfs_open(const char *path, int flags, int accessMode) {
	ESP_LOGI(tag, ">> open path=%s, flags=0x%x, accessMode=0x%x", path, flags, accessMode);
	logFlags(flags);
	return -1;
}


static int vfs_close(int fd) {
	ESP_LOGI(tag, ">> close fd=%d", fd);
	return 0;
}


static int vfs_fstat(int fd, struct stat *st) {
	ESP_LOGI(tag, ">> fstat fd=%d", fd);
	return 0;
}


static int vfs_stat(const char *path, struct stat *st) {
	ESP_LOGI(tag, ">> stat path=%s", path);
	return 0;
}


static int vfs_link(const char *oldPath, const char *newPath) {
	ESP_LOGI(tag, ">> link oldPath=%s, newPath=%s", oldPath, newPath);
	return 0;
}


static int vfs_rename(const char *oldPath, const char *newPath) {
	ESP_LOGI(tag, ">> rename oldPath=%s, newPath=%s", oldPath, newPath);
	return 0;
}


/**
 * Register the VFS at the specified mount point.
 * The callback functions are registered to handle the
 * different functions that may be requested against the
 * VFS.
 */
void registerTestVFS(char *mountPoint) {
	esp_vfs_t vfs;
	esp_err_t err;

	vfs.fd_offset = 0;
	vfs.flags = ESP_VFS_FLAG_DEFAULT;
	vfs.write  = vfs_write;
	vfs.lseek  = vfs_lseek;
	vfs.read   = vfs_read;
	vfs.open   = vfs_open;
	vfs.close  = vfs_close;
	vfs.fstat  = vfs_fstat;
	vfs.stat   = vfs_stat;
	vfs.link   = vfs_link;
	vfs.rename = vfs_rename;

	err = esp_vfs_register(mountPoint, &vfs, NULL);
	if (err != ESP_OK) {
		ESP_LOGE(tag, "esp_vfs_register: err=%d", err);
	}
} // End of registerTestVFS
