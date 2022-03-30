set(INCLUDES
    bencode/bdata.h
    bencode/bdict.h
    bencode/bencode.h
    bencode/bint.h
    bencode/blist.h
    bencode/bstring.h
    bencode/btypes.h
    bencode/decode.h
    bencode/encode.h
    bencode/error.h
    bencode/utils.h
)

install(FILES ${INCLUDES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bencode)