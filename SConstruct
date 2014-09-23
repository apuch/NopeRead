import os

gtest_dir = Dir('#/3rdParty/gtest-1.7.0').abspath
lemon_dir = Dir('#/3rdParty/lemon-parser').abspath
src_dir = Dir('#/src').abspath

CPPPATH = [ src_dir ]

env = Environment(CPPPATH=CPPPATH)
env['CROSS_BUILD'] = None
env['gtest_dir'] = gtest_dir
env['lemon_dir'] = lemon_dir

env['variant_main']  = Dir('#/build/main').abspath
env['variant_test']  = Dir('#/build/test').abspath
env['variant_lemon'] = Dir('#/build/lemon').abspath
env['variant_gtest'] = Dir('#/build/gtest').abspath

env['variant_dir'] = env['variant_lemon']
SConscript('3rdParty/lemon.scons', 
    variant_dir = env['variant_lemon'], 
    exports = ['env'])


bld = Builder( \
    action = 
        'cp -f %s . &&' % env['lemon_par'] + 
        '%s $SOURCE' % env['lemon_exe'],
    suffix = '.c',
    src_suffix = '.yy'
)
env['BUILDERS']['Lemon'] = bld


env['variant_dir'] = env['variant_main']
SConscript('src/main.scons', 
    variant_dir = env['variant_dir'], 
    exports = ['env'])

unittest = int(ARGUMENTS.get('UNITTEST', 0))
if unittest:
    env['variant_dir'] = env['variant_gtest']
    SConscript('3rdParty/gtest.scons', 
        variant_dir = env['variant_dir'], 
        exports = ['env'])

    env['variant_dir'] = env['variant_test']
    SConscript('test/test.scons', 
        variant_dir = env['variant_dir'], 
        exports = ['env'])


