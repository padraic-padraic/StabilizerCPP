root = fullfile('/Users','padraic', 'Documents', 'PhD', 'StabilizerCPP');
inc_path = fullfile(root,'src');
static_lib = fullfile(root,'out','libsymplectic_stabilizer.a');
mex('-v','CXXFLAGS="$CXXFLAGS -std=c++11"',['-I',inc_path],static_lib,'mex_random_stabilizer.cpp');
mex('-v','CXXFLAGS="$CXXFLAGS -std=c++11"',['-I',inc_path],static_lib,'mex_random_states.cpp');
