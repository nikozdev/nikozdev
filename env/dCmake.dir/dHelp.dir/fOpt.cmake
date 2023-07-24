cmake_minimum_required(VERSION 3.3...3.8)
include_guard(GLOBAL)
# actions
function(fOptEnum oOptPick vOptList vOptDesc)
    set(${oOptPick} ${${oOptPick}} CACHE STRING ${vOptDesc})
    set_property(CACHE ${oOptPick} PROPERTY STRINGS ${${vOptList}})
endfunction(fOptEnum)
