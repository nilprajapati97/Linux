#Embedded hashtag#Linux, what is the difference between a static library (.a) and a shared library (.so)? Why would you choose one over the other in an embedded project?

💡 Let’s learn together! Subscribe to my YouTube channel for more tech content:
https://lnkd.in/dB6SfvFn

📌 Static Library (.a)

A static library is a collection of object files bundled into one .a file.

When you compile and link your application, the required functions from the static library are copied directly into the executable.

This means the final binary is self-contained.


✅ Pros:

No dependency on external library at runtime → just run the binary.

Useful in embedded systems where dynamic linking may not be supported.


❌ Cons:

Larger binary size (because code is duplicated in each binary that uses it).

If you update the library, you must rebuild all applications using it.


📌 Shared Library (.so)

A shared library (.so = shared object) is loaded at runtime.

Multiple programs can share the same .so file in memory.

The application contains only references → the actual functions are loaded when the program runs.


✅ Pros:

Saves memory (shared across processes).

Easier to update/patch (just replace .so without recompiling apps).

Smaller executable size.


❌ Cons:

Dependency management (must ensure the correct .so version is present).

Slight runtime overhead due to dynamic linking.


📌 Embedded Use Case

Static library (.a):
Good for small MCUs or very resource-constrained embedded Linux, where you want one standalone binary with no external dependencies. Example: deploying a firmware tool.

Shared library (.so):
Better for complex systems (like your STBs, routers, or IoT gateways) where multiple apps share common functionality (e.g., JSON parser, MQTT library). Saves memory and makes updating easier.


✅ Final Answer:

"A static library (.a) is linked into the application at compile time, making the final binary self-contained but larger. A shared library (.so) is loaded at runtime, allowing multiple applications to share the same code, saving memory but requiring dependency management. In embedded projects, I would use static libraries for simple standalone binaries, and shared libraries when multiple applications need to reuse the same functionality, like networking or JSON parsing."