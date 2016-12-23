package main

// #include <stdlib.h>
// #include "wrapper.c"
import "C"
import "unsafe"
import "math/rand"
import "time"

func main() {

	rand.Seed(time.Now().UTC().UnixNano())

	fd := C.my_fb_open()

	buf := C.my_fb_map(fd)

	test := (*[320 * 200 * 3]byte)(unsafe.Pointer(buf))

	for i := 0; i < len(test); i++ {
		test[i] = (byte)(rand.Intn(255))
	}
	// do stuff here
	C.my_fb_unmap(buf)

	C.my_fb_close(fd)
}
