# Build with examples

By default, examples in ``examples/`` are not build.  To enable them, use
``--with-examples`` configure option:

    ./waf configure --with-examples
    ./waf


To run examples:

    # trivial Sensor node
    ./build/examples/Sensor

    # trivial Processor node
    ./build/examples/MotionProcessor

    # trivial Actuator node 
    ./build/examples/Actuator

If you want to test out a sample IoT Node, just create a ``.cpp`` file in ``examples/``
folder and it will be compiled on the next run on ``./waf``.  For example:

    cp examples/consumer.cpp examples/my-new-processor.cpp
    ./waf
    ./build/examples/my-new-processor