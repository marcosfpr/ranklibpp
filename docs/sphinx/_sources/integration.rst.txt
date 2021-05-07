Integration
###########

Prerequisites
*************

The main prerequisite for installing ltr++ is CMake 3.15 or higher. Other external libraries will be downloaded automatically,
if you don't have they. So that make sure you have CMake installed. Also, make sure that your operating system is compatible with 
any build that is working: 

+--------------------+-------------------------------------------------------------------------------------------------------------+
|       System       |                                                        1.0.0                                                |
+====================+=============================================================================================================+
|     Windows x86    |  |Passing|                                                                                                  |
+--------------------+-------------------------------------------------------------------------------------------------------------+
|     Windows x64    |  |Passing|                                                                                                  |
+--------------------+-------------------------------------------------------------------------------------------------------------+
|     MacOSX x64     |  |Passing|                                                                                                  |
+--------------------+-------------------------------------------------------------------------------------------------------------+
|     Linux x64      |  |Passing|                                                                                                  |
+--------------------+-------------------------------------------------------------------------------------------------------------+

.. |Passing| image:: https://img.shields.io/badge/build-passing-brightgreen

1. C++
***********
Using CMake and certifying that all prerequisites are ok, let's understand how to build and install ltr.

Including header-only 
---------------------

After installing the ltr library, you can import the library as a header-only file:

.. code-block:: c
  :linenos:

  #include <ltr.hpp>

.. warning::
   Make sure you have C++17 or higher installed.

Embed as CMake subdirectory
---------------------------

You can use ltr++ directly in CMake projects as a subproject.

Clone the whole project inside your own project:

.. code-block:: bash
  :linenos:

  $ git clone https://github.com/marcosfpr/ltrpp/


and add the subdirectory to your CMake script:

.. code-block:: cmake
  :linenos:

  add_subdirectory(ltrpp)


When creating your executable, link the library to the targets you want:

.. code-block:: cmake
  :linenos:

  add_executable(my_target main.cpp)
  target_link_libraries(my_target PRIVATE ltr)


Your target will be able to see the ltr++ headers now.

Embed with CPM.cmake
--------------------

`CPM.cmake`_ is a nice wrapper around the CMake FetchContent function.
Install `CPM.cmake`_ and then use this command to add ltr++ to your build
script:

.. _`CPM.cmake`: https://github.com/TheLartians/CPM.cmake

.. code-block:: cmake
  :linenos:

  CPMAddPackage(
          NAME ltr
          GITHUB_REPOSITORY marcosfpr/ltrpp
          GIT_TAG origin/master # or whatever tag you want
  )
  # ...
  target_link_libraries(my_target PUBLIC ltr)


Your target will be able to see the ltr++ headers now.

Find as CMake package
---------------------

If you are using CMake and have the library installed on your system, you can then find ltr++ with the
usual ``find_package`` command:

.. code-block:: cmake
  :linenos:

  find_package(ltr REQUIRED)
  # ...
  target_link_libraries(my_target PUBLIC ltr)


Your target will be able to see the ltr++ headers now.

.. warning::

    There is no easy default directory for ``find_package`` on windows. You have
    to `set it`_ yourself.

.. _`set it`: https://stackoverflow.com/questions/21314893/what-is-the-default-search-path-for-find-package-in-windows-using-cmake



2. Python
***********

Development stage


3. Installing
**************

Development stage


4. Building
***********

4.1 Update C++
--------------

Update your C++ compiler to at least C++17:

**Ubuntu:**

.. code-block:: bash
    :linenos:

    # install GCC10
    sudo apt install build-essential
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt install gcc-10
    sudo apt install g++-10
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 10
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 10
    # Choose gcc-10 there as the default compiler
    update-alternatives --config g++

**Mac OS:**

.. code-block:: bash
    :linenos:

    # Download clang
    curl --output clang.tar.xz -L https://github.com/llvm/llvm-project/releases/download/llvmorg-11.0.0/clang+llvm-11.0.0-x86_64-apple-darwin.tar.xz
    mkdir clang
    tar -xvJf clang.tar.xz -C clang
    # Copy the files to use/local
    cd clang/clang+llvm-11.0.0-x86_64-apple-darwin
    sudo cp -R * /usr/local/
    # Make it your default compiler
    export CXX=/usr/local/bin/clang++

**Windows:**

  Update your `Visual Studio Compiler`_

.. _`Visual Studio Compiler`: https://visualstudio.microsoft.com/


4.2 Building the projet
-----------------------

After installing or updating the dependencies, clone the project with:

.. code-block:: bash
    :linenos:

    git clone https://github.com/marcosfpr/ltrpp.git
    cd pareto 

And then build with:

**Ubuntu:**

.. code-block:: bash
    :linenos:
    
    mkdir build
    cd build
    cmake -version
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O2"
    cmake --build . -j 2 --config Release
    # The next command for installing
    sudo cmake --install .
    # The next command for building the packages / installers
    sudo cpack .

**Mac OS:**

.. code-block:: bash
    :linenos:

    mkdir build
    cd build
    cmake -version
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O2"
    cmake --build . -j 2 --config Release
    # The next command for installing
    cmake --install .
    # The next command for building the packages / installers
    cpack .


**Windows:**

.. code-block:: bash
    :linenos:

    mkdir build
    cd build
    cmake -version
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="/O2"
    cmake --build . -j 2 --config Release
    # The next command for installing
    cmake --install .
    # The next command for building the packages / installers
    cpack .


Python
------

  Development stage
