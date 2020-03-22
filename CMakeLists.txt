cmake_minimum_required(VERSION 3.10)

project(einstein)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_definitions(-DTARGET_API_MAC_OSX -DTARGET_OS_OPENSTEP)

add_executable(einstein 
	main.cpp
	event.cpp
	window.cpp
	TARMProcessor.cpp
	TCondVar.cpp
	TDMAManager.cpp
	TEmulator.cpp
	TEOFException.cpp
	TError.cpp
	TException.cpp
	TFileManager.cpp
	TFileStream.cpp
	TFlash.cpp
	TFlatROMImageWithREX.cpp
	THostInfo.cpp
	TInterruptManager.cpp
	TIOException.cpp
	TJITCache.cpp
	TJITGeneric.cpp
	TJITGeneric_BlockDataTransfer.cpp
	TJITGeneric_DataProcessingPSRTransfer_ArithmeticOp.cpp
	TJITGeneric_DataProcessingPSRTransfer_LogicalOp.cpp
	TJITGeneric_DataProcessingPSRTransfer_MoveOp.cpp
	TJITGeneric_DataProcessingPSRTransfer_MRS.cpp
	TJITGeneric_DataProcessingPSRTransfer_MSR.cpp
	TJITGeneric_DataProcessingPSRTransfer.cpp
	TJITGeneric_DataProcessingPSRTransfer_TestOp.cpp
	TJITGeneric_Multiply.cpp
	TJITGeneric_MultiplyAndAccumulate.cpp
	TJITGeneric_Other.cpp
	TJITGeneric_SingleDataSwap.cpp
	TJITGeneric_SingleDataTransfer.cpp
	TJITGeneric_Test.cpp
	TJITGenericPage.cpp
	TJITGenericROMPatch.cpp
	TJITPage.cpp
	TLinearCard.cpp
	TLog.cpp
	TMappedFile.cpp
	TMemError.cpp
	TMemory.cpp
	TMutex.cpp
	TMMU.cpp
	TNativePrimitives.cpp
	TNE2000Card.cpp
	TNetworkManager.cpp
	TNullSoundManager.cpp
	TSDLScreenManager.cpp
	TSoundManager.cpp
	TPCMCIACard.cpp
	TPCMCIAController.cpp
	TPlatformManager.cpp
	TROMImage.cpp
	TScreenManager.cpp
	TSerialPortManager.cpp
	TStdOutLog.cpp
	TStream.cpp
	TThread.cpp
	TVirtualizedCalls.cpp
	TVirtualizedCallsPatches.cpp
	UUTF16CStr.cpp
	UUTF16Conv.cpp
)

target_link_libraries(einstein ${SDL2_LIBRARIES} "-framework AddressBook -framework Foundation")

