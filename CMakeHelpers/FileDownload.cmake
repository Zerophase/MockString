function(FileDownload url file_path expected_hash)
	file(DOWNLOAD ${url}
	     "${CMAKE_SOURCE_DIR}/${file_path}"
	     SHOW_PROGRESS
	     STATUS status
	     EXPECTED_HASH ${expected_hash}
	     LOG log
	     )

	list(GET status 0 status_code)
	list(GET status 1 status_string)
	if(NOT status_code EQUAL 0)
		message(FATAL_ERROR "Error: downloading
            '${CMAKE_SOURCE_DIR}/${file_path}' failed
            status_code: ${status_code}
            status_string: ${status_string}
            Log: ${log}
        ")
	endif()
endfunction()
