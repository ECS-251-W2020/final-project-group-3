file(REMOVE_RECURSE
  "libnuraft.a"
  "libnuraft.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/static_lib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
