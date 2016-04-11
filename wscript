# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-
VERSION = '0.1'
APPNAME = 'ndn-iot'

from waflib import Build, Logs, Utils, Task, TaskGen, Configure

def options(opt):
    opt.load('compiler_c compiler_cxx gnu_dirs')
    opt.load('boost default-compiler-flags doxygen curlpp', tooldir=['.waf-tools'])

    ropt = opt.add_option_group('ndn-iot Options')

    ropt.add_option('--with-tests', action='store_true', default=False, dest='with_tests',
                    help='''build unit tests''')

    
    ropt.add_option('--with-examples', action='store_true', default=False, dest='with_examples',
                    help='''Build examples''')

def configure(conf):
    conf.load("compiler_c compiler_cxx gnu_dirs boost default-compiler-flags curlpp")

    conf.check_cfg(package='libndn-cxx', args=['--cflags', '--libs'],
                   uselib_store='NDN_CXX', mandatory=True)
    
    conf.check_curlpp(mandatory=True)

    if conf.options.with_tests:
        conf.env['WITH_TESTS'] = True
    
    conf.env['WITH_EXAMPLES'] = conf.options.with_examples

    USED_BOOST_LIBS = ['system', 'iostreams', 'filesystem', 'random']
    if conf.env['WITH_TESTS']:
        USED_BOOST_LIBS += ['unit_test_framework']
    conf.check_boost(lib=USED_BOOST_LIBS, mandatory=True)

    try:
        conf.load("doxygen")
    except:
        pass

   
    
    conf.write_config_header('src/config.hpp', define_prefix='IOT_API_')

def build(bld):
    

    bld(target="ndn-iot",
    	name="ndn-iot",
        features=["cxx", "cxxstlib"],
        #source=bld.path.ant_glob(['src/main.cpp']),
        source=bld.path.ant_glob(['src/**/*.cpp'],
                                 excl=['src/main.cpp']),
        use='NDN_CXX BOOST CURLPP',
        includes="src",
        export_includes="src",
        )

    # Tests
    bld.recurse('tests')


    # Modules
  

    bld.recurse("examples")

