import copy
import os
env = Environment(ENV = os.environ)


ddk_home = '/home/ubuntu/hiai-studio-rt/tools/che/ddk/ddk/'

libs=[
        'matrix',
        'pthread',
        'protobuf',
        'drvhdc_host',
        'crypto',
        'c_sec', 
        'pthread', 
]

static_libs = [
]


cpp_flags = ['-pthread', '-fPIC', '-fopenmp', '-O2', '-std=c++11']

lib_path = [
        ddk_home + 'lib/x86_64-linux-gcc5.4',
]

inc_path = [
        './inc/',
        ddk_home + 'include/inc',
        ddk_home + 'include/third_party/protobuf/include',
        ddk_home + 'include/third_party/cereal/include',
        ddk_home + 'include/libc_sec/include',
]

link_flags = copy.copy(cpp_flags) + ['-Wl,--rpath=.:./lib:../lib:../lib/linux:../build/lib']

cpp_defines = []


src = Glob('./src/*.cpp') 
test_batch = env.Program(
        target = 'test_ssd',
        source = src ,
        LIBS = libs,
        LIBPATH = lib_path,
        CPPFLAGS = cpp_flags,
        #LINKFLAGS = link_flags + ['-Wl,--whole-archive', libcaffe, '-Wl,--no-whole-archive',],
        LINKFLAGS = link_flags, 
        CPPPATH = inc_path,
)

Default([test_batch])
