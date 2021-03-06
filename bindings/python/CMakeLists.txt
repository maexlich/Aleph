IF( BUILD_PYTHON_BINDINGS )
  FIND_PACKAGE( pybind11 )
  IF( PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND AND PYBIND11_FOUND )
    INCLUDE_DIRECTORIES(
      ${PYTHON_INCLUDE_DIRS}
      ${PYBIND11_INCLUDE_DIRS}
    )

    ADD_LIBRARY( aleph SHARED aleph.cc )

    # The library must not have any prefix and should be located in
    # a subfolder that includes the package name. The setup will be
    # more complicated otherwise.
    SET_TARGET_PROPERTIES( aleph
      PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/aleph"
    )

    IF( APPLE )
      SET_TARGET_PROPERTIES( aleph
        PROPERTIES
          LINK_FLAGS "-undefined dynamic_lookup"
          SUFFIX     ".so"
      )
    ENDIF()

    IF( HDF5_FOUND )
      TARGET_INCLUDE_DIRECTORIES( aleph SYSTEM
        PUBLIC
          ${HDF5_INCLUDE_DIRS}
          ${HDF5_CXX_INCLUDE_DIRS}
      )
      TARGET_LINK_LIBRARIES( aleph
        ${HDF5_CXX_LIBRARIES}
      )
    ENDIF()

    IF( FLANN_FOUND AND FLANN_VERSION VERSION_GREATER "1.8.4" )
      TARGET_LINK_LIBRARIES( aleph lz4 )
    ENDIF()
  ELSE()
    MESSAGE( STATUS "Cannot build Python bindings because no suitable version of Python was found" )
  ENDIF()

  # Place the initialization file in the output directory for the Python
  # bindings. This will simplify the installation.
  CONFIGURE_FILE( __init__.py
    ${CMAKE_CURRENT_BINARY_DIR}/aleph/__init__.py
  )

  # Ditto for the setup file.
  CONFIGURE_FILE( setup.py
    ${CMAKE_CURRENT_BINARY_DIR}/aleph/setup.py
  )
ENDIF()
