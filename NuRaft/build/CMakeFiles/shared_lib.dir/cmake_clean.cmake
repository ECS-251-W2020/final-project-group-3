file(REMOVE_RECURSE
  "libnuraft.dylib"
  "libnuraft.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/shared_lib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
