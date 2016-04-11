
# NamedIoT: In-Network composition
==========================================


# Setup the build environment

This setup section describes the build setup, the examples setup, and the emulation using  ``Mini-NDN`` 

## Downloading from Git

The first step is to obtain the source code for ``NamedIoT`` and, its main dependency, the
``ndn-cxx`` library.  

    # Download ndn-cxx
    git clone https://github.com/named-data/ndn-cxx

    # Download NamedIoT
    git clone https://github.com/usnistgov/NamedIoT

## Prerequisites

-  Install the `ndn-cxx library <http://named-data.net/doc/ndn-cxx/current/INSTALL.html>` and its requirements
-  Install the `client-side URL transfer library`

    sudo apt-get install libcurlpp-dev
    sudo apt-get install libcurl4-openssl-dev


## Build sources

The following basic commands should be used to build  ``NamedIoT``  on Ubuntu:

    ./waf configure
    ./waf
    sudo ./waf install

## Build with examples

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

## Run the emulation

In order to run the emulation, you need to install ``Mini-NDN`` and use it to run the topology described in ``./simulation/IotHome.conf`` 

The  ``./simulation/IotHome.mnndn`` contains the topology file that you can edit using ``Mini-NDN Edit``  GUI program 

### Installing Mini-NDN

If you have all the dependencies installed simply clone this repository and run:

    sudo ./install.sh -i

else if you don't have the dependencies:

    sudo ./install.sh -mrfti

### Running the topology 

To run Mini-NDN with the IoT Home topology file, provide the filename as the first argument:

    sudo minindn ./simulation/IotHome.conf


## **EXPERIMENTAL** Visualization tool

The ``./simulation/Emergency`` contains advanced Emergency response use case as **Work In Progress**





# Research context 

## Overview 

Composition of IoT devices into CPS in one of the challenges on modern architecture. The composition solutions relay on applications to orchestrate the interaction between the components of the system. ANTD is working on a novel approach to express the composition using NDN naming power. Moreover, this approach bypasses the need of a composition engine by providing in-network composition capabilities.

## Context

As devices with sensors and actuators connect to the Internet, they become "smart objects" and form a foundation for the Internet of Things (IoT). The full potential of IoT does not lie in simple remote access to data from smart objects. Instead, it is the intersection of networked services with the physical world that will result in a Cyber Physical System (CPS) that will bring about tremendous benefits. The potential economic benefit of the development and deployment of CPS/IoT systems is very significant. Indeed, studies suggest that these systems will provide important economic productivity gain and be a significant new growth engine for the US economy. 
  As the deployment of stand-alone CPS/IoT systems is starting to take place in a number of domains, the current trend is to develop a common set of protocols for a unified and defragmented CPS/IoT platform. To achieve such goal, solutions have been proposed for a platform built as an overlay on top of today's host-centric Internet. These include Bluemix and Fiware platforms as recently presented during the smart city workshop [1] (NIST – Global City Teams Challenge 2015).
  However, there is a fundamental mismatch between the host-centric nature of today's Internet and the information-centric nature of CPS/IoT systems (and of the current Internet usage in general). To address the mismatch between today's Internet and its new usage model, a novel Information-Centric Networking (ICN) paradigm has emerged. The most prominent instance of the ICN paradigm is Named Data Networking (NDN) promoted by major router vendors and US universities. The ICN/NDN architecture can bring tremendous benefits to CPS/IoT. NDN uses in-network caching for bandwidth efficiency, has built-in security, and offers ease of application development through proper naming of application objects. 
 We will leverage these NDN features to address the fundamental challenges to efficient CPS/IoT services. In particular, the proper use of the rich naming functionality and use of modularity and composability for reliable and verifiable assembly of CPS/IoT components. While service composition is a major challenge for CPS/IoT deployments, today's solutions rely on applications to orchestrate the interaction between the different components of the system. Our proposal is based on a novel approach to express the composition using NDN naming capability. Moreover, this approach bypasses the need of a composition engine by providing in-network composition capabilities.
  

## Technical plan

  1. Develop a framework for efficient service composition in CPS/IoT systems: We will address the problem for composing a number of actions to achieve complex CPS tasks using the rich object naming capabilities of NDN. This approach allows for distributed in-network processing and uses NDN's dynamic forwarding to achieve dynamically adaptive composition, such as balancing the processing load among all capable nodes. We will study the algorithmic foundation of the composition and identify common functional and technical requirements.  Formal methods will be used for rigorous definition of the features that will result in an intelligent, fast, and distributed composition engine.  Once an initial architecture and implementation is defined, we will make use of verification tools to prove the main properties of the implementation, such as resilience to node failures. These results should be able to be extended in the future to achieve a reference architecture and implementation. 
  2. Naming strategy and associated metrics: Naming is at the heart of the future internet architecture based on NDN. We will develop a strategy for naming and name assignment for CPS/IoT applications. Different applications may need different name space design choices. Since our composition approach uses name hierarchy to define the composition logic, we need to define appropriate metrics to quantify properties related to naming. We will make use of the fact that hierarchical names give rise to the notion of distance between named objects that is a function of the topology of the name tree. Obviously, any measure we come up with for the goodness of a naming scheme should be generalizable across a wide range of CPS/IoT applications.
  3. Use cases and prototype experimentation: We will take advantage of use cases from the NIST CPS program [2] to illustrate the benefits of NDN-based naming and composition as compared to current service composition for CPS/IoT applications. We will carry out limited-scale experiments using actual IoT deployment with low-cost IoT devices for a subset of use cases to illustrate the interoperability that can be achieved using NDN-based standard composition across different application scenarios. In addition to advantages over IP-based solutions, insights gained from actual application development should allow us to discover any needed NDN enhancements and propose corresponding interoperable solutions that can be generalized to multiple CPS/IoT domains. 
  
## Potential impact

This work will enable increased understanding of how to intelligently and effectively design and manage CPS/IoT applications and help position ITL as a major player in maturing the emerging future internet architecture technologies for such applications. It will benefit IoT standardization effort when it moves to IETF, it is currently being discussed within the ICN Research Group of IRTF [3].


## References
\[1\] [Global cities team challenge](http://www.nist.gov/cps/global-cities-team-challenge-2015.cfm)

\[2\] [Cyber-Physical Systems Framework](http://www.cpspwg.org/Portals/3/docs/CPS%20PWG%20Draft%20Framework%20for%20Cyber-Physical%20Systems%20Release%200.8%20September%202015.pdf)

\[3\] [IoT Challenges](https://tools.ietf.org/html/draft-zhang-iot-icn-challenges-02)

