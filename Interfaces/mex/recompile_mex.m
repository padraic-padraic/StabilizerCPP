root = fullfile('/Users','padraic', 'Documents','UCL', 'PhD', 'StabilizerCPP');
eigen_path = fullfile(root,'dependencies','eigen');
dbitset_path = fullfile('/usr','local','include');
inc_path = fullfile(root,'src');
static_lib = fullfile(root,'out','libsymplectic_stabilizer.a');
mex('-v','CXXFLAGS="$CXXFLAGS -std=c++11"',['-I',inc_path], ['-I', eigen_path], ['-I', dbitset_path], static_lib,'mex_random_stabilizer.cpp');
% mex('-v','CXXFLAGS="$CXXFLAGS -std=c++11"',['-I',inc_path],['-I', eigen_path], ['-I', dbitset_path], static_lib,'mex_random_states.cpp');
% TODO: Copy the mex example to fix this pointer error.