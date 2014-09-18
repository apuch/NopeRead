gtest_dir = Dir('#/3rdParty/gtest-1.7.0').abspath
src_dir = Dir('#/src').abspath
CPPPATH = [ src_dir ]

env = Environment(CPPPATH=CPPPATH)
env['CROSS_BUILD'] = None
env['gtest_dir'] = gtest_dir

env['variant_dir'] = Dir('#/built/main').abspath
SConscript('src/main.scons', 
    variant_dir = env['variant_dir'], 
    exports = ['env'])

unittest = int(ARGUMENTS.get('UNITTEST', 0))
if unittest:
    env['variant_dir'] = Dir('#/built/gtest').abspath
    SConscript('3rdParty/gtest.scons', 
        variant_dir = env['variant_dir'], 
        exports = ['env'])

    env['variant_dir'] = Dir('#/built/test').abspath
    SConscript('test/test.scons', 
        variant_dir = env['variant_dir'], 
        exports = ['env'])


