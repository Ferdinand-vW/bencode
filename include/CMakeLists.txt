set(INCLUDES
    bdata.h
    bdict.h
    bencode.h
    bint.h
    blist.h
    bstring.h
    btypes.h
    decode.h
    encode.h
    error.h
    utils.h
)

install(FILES ${INCLUDES} DESTINATION "${INSTALL_INCLUDE_DIR}/bencode")