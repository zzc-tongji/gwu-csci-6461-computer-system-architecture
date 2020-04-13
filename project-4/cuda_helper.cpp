#include <stdio.h>
#include "cuda_helper.h"

int CudaDeviceList()
{
  int count;
  CudaErrorHandler(cudaGetDeviceCount(&count));
  cudaDeviceProp prop;
  if (count == 0)
  {
    fprintf(stdout, "There is no CUDA device.");
    printf("");
  }
  for (int i = 0; i < count; i++)
  {
    CudaErrorHandler(cudaGetDeviceProperties(&prop, i));
    printf("CUDA device:                                       #%d\n", i);
    printf("ASCII string identifying device:                   %s\n", prop.name);
    printf("Number of asynchronous engines:                    %d\n", prop.asyncEngineCount);
    printf("Clock frequency in kilohertz:                      %d\n", prop.clockRate);
    printf("Major and minor compute capability:                %d.%d\n", prop.major, prop.minor);
    printf("Maximum size of each dimension of a grid:          %d / %d / %d\n", prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
    printf("Maximum size of each dimension of a block:         %d / %d / %d\n", prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
    printf("Maximum resident threads per multiprocessor:       %d\n", prop.maxThreadsPerMultiProcessor);
    printf("Maximum number of threads per block:               %d\n", prop.maxThreadsPerBlock);
    printf("Maximum pitch in bytes allowed by memory copies:   %zu\n", prop.memPitch);
    printf("Number of multiprocessors on device:               %d\n", prop.multiProcessorCount);
    printf("32-bit registers available per block:              %d\n", prop.regsPerBlock);
    printf("Shared memory available per block in bytes:        %zu\n", prop.sharedMemPerBlock);
    printf("Alignment requirement for textures:                %zu\n", prop.textureAlignment);
    printf("Constant memory available on device in bytes:      %zu\n", prop.totalConstMem);
    printf("Global memory available on device in bytes:        %zu\n", prop.totalGlobalMem);
    printf("Warp size in threads (per SM):                     %d\n", prop.warpSize);
    printf("\n");
  }
  return count;
}

void CudaErrorHandler(cudaError_t error)
{
  if (error == cudaSuccess)
  {
    return;
  }
  fprintf(stderr, "[%d] ", error);
  switch (error)
  {
  case cudaErrorInvalidValue:
    fprintf(stderr, "This indicates that one or more of the parameters passed to the API call is not within an acceptable range of values.");
    break;
  case cudaErrorMemoryAllocation:
    fprintf(stderr, "The API call failed because it was unable to allocate enough memory to perform the requested operation.");
    break;
  case cudaErrorInitializationError:
    fprintf(stderr, "The API call failed because the CUDA driver and runtime could not be initialized.");
    break;
  case cudaErrorCudartUnloading:
    fprintf(stderr, "This indicates that a CUDA Runtime API call cannot be executed because it is being called during process shut down, at a point in time after CUDA driver has been unloaded.");
    break;
  case cudaErrorProfilerDisabled:
    fprintf(stderr, "This indicates profiler is not initialized for this run. This can happen when the application is running with external profiling tools like visual profiler.");
    break;
  case cudaErrorInvalidConfiguration:
    fprintf(stderr, "This indicates that a kernel launch is requesting resources that can never be satisfied by the current device. Requesting more shared memory per block than the device supports will trigger this error, as will requesting too many threads or blocks. See cudaDeviceProp for more device limitations.");
    break;
  case cudaErrorInvalidPitchValue:
    fprintf(stderr, "This indicates that one or more of the pitch-related parameters passed to the API call is not within the acceptable range for pitch.");
    break;
  case cudaErrorInvalidSymbol:
    fprintf(stderr, "This indicates that the symbol name/identifier passed to the API call is not a valid name or identifier.");
    break;
  case cudaErrorInvalidTexture:
    fprintf(stderr, "This indicates that the texture passed to the API call is not a valid texture.");
    break;
  case cudaErrorInvalidTextureBinding:
    fprintf(stderr, "This indicates that the texture binding is not valid. This occurs if you call cudaGetTextureAlignmentOffset() with an unbound texture.");
    break;
  case cudaErrorInvalidChannelDescriptor:
    fprintf(stderr, "This indicates that the channel descriptor passed to the API call is not valid. This occurs if the format is not one of the formats specified by cudaChannelFormatKind, or if one of the dimensions is invalid.");
    break;
  case cudaErrorInvalidMemcpyDirection:
    fprintf(stderr, "This indicates that the direction of the memcpy passed to the API call is not one of the types specified by cudaMemcpyKind.");
    break;
  case cudaErrorInvalidFilterSetting:
    fprintf(stderr, "This indicates that a non-float texture was being accessed with linear filtering. This is not supported by CUDA.");
    break;
  case cudaErrorInvalidNormSetting:
    fprintf(stderr, "This indicates that an attempt was made to read a non-float texture as a normalized float. This is not supported by CUDA.");
    break;
  case cudaErrorInsufficientDriver:
    fprintf(stderr, "This indicates that the installed NVIDIA CUDA driver is older than the CUDA runtime library. This is not a supported configuration. Users should install an updated NVIDIA display driver to allow the application to run.");
    break;
  case cudaErrorInvalidSurface:
    fprintf(stderr, "This indicates that the surface passed to the API call is not a valid surface.");
    break;
  case cudaErrorDuplicateVariableName:
    fprintf(stderr, "This indicates that multiple global or constant variables (across separate CUDA source files in the application) share the same string name.");
    break;
  case cudaErrorDuplicateTextureName:
    fprintf(stderr, "This indicates that multiple textures (across separate CUDA source files in the application) share the same string name.");
    break;
  case cudaErrorDuplicateSurfaceName:
    fprintf(stderr, "This indicates that multiple surfaces (across separate CUDA source files in the application) share the same string name.");
    break;
  case cudaErrorDevicesUnavailable:
    fprintf(stderr, "This indicates that all CUDA devices are busy or unavailable at the current time. Devices are often busy/unavailable due to use of cudaComputeModeExclusive, cudaComputeModeProhibited or when long running CUDA kernels have filled up the GPU and are blocking new work from starting. They can also be unavailable due to memory constraints on a device that already has active CUDA work being performed.");
    break;
  case cudaErrorIncompatibleDriverContext:
    fprintf(stderr, "This indicates that the current context is not compatible with this the CUDA Runtime. This can only occur if you are using CUDA Runtime/Driver interoperability and have created an existing Driver context using the driver API. The Driver context may be incompatible either because the Driver context was created using an older version of the API, because the Runtime API call expects a primary driver context and the Driver context is not primary, or because the Driver context has been destroyed. Please see Interactions with the CUDA Driver API for more information.");
    break;
  case cudaErrorMissingConfiguration:
    fprintf(stderr, "The device function being invoked (usually via cudaLaunchKernel()) was not previously configured via the cudaConfigureCall() function.");
    break;
  case cudaErrorLaunchMaxDepthExceeded:
    fprintf(stderr, "This error indicates that a device runtime grid launch did not occur because the depth of the child grid would exceed the maximum supported number of nested grid launches.");
    break;
  case cudaErrorLaunchFileScopedTex:
    fprintf(stderr, "This error indicates that a grid launch did not occur because the kernel uses file-scoped textures which are unsupported by the device runtime. Kernels launched via the device runtime only support textures created with the Texture Object API's.");
    break;
  case cudaErrorLaunchFileScopedSurf:
    fprintf(stderr, "This error indicates that a grid launch did not occur because the kernel uses file-scoped surfaces which are unsupported by the device runtime. Kernels launched via the device runtime only support surfaces created with the Surface Object API's.");
    break;
  case cudaErrorSyncDepthExceeded:
    fprintf(stderr, "This error indicates that a call to cudaDeviceSynchronize made from the device runtime failed because the call was made at grid depth greater than than either the default (2 levels of grids) or user specified device limit cudaLimitDevRuntimeSyncDepth. To be able to synchronize on launched grids at a greater depth successfully, the maximum nested depth at which cudaDeviceSynchronize will be called must be specified with the cudaLimitDevRuntimeSyncDepth limit to the cudaDeviceSetLimit api before the host-side launch of a kernel using the device runtime. Keep in mind that additional levels of sync depth require the runtime to reserve large amounts of device memory that cannot be used for user allocations.");
    break;
  case cudaErrorLaunchPendingCountExceeded:
    fprintf(stderr, "This error indicates that a device runtime grid launch failed because the launch would exceed the limit cudaLimitDevRuntimePendingLaunchCount. For this launch to proceed successfully, cudaDeviceSetLimit must be called to set the cudaLimitDevRuntimePendingLaunchCount to be higher than the upper bound of outstanding launches that can be issued to the device runtime. Keep in mind that raising the limit of pending device runtime launches will require the runtime to reserve device memory that cannot be used for user allocations.");
    break;
  case cudaErrorInvalidDeviceFunction:
    fprintf(stderr, "The requested device function does not exist or is not compiled for the proper device architecture.");
    break;
  case cudaErrorNoDevice:
    fprintf(stderr, "This indicates that no CUDA-capable devices were detected by the installed CUDA driver.");
    break;
  case cudaErrorInvalidDevice:
    fprintf(stderr, "This indicates that the device ordinal supplied by the user does not correspond to a valid CUDA device.");
    break;
  case cudaErrorStartupFailure:
    fprintf(stderr, "This indicates an internal startup failure in the CUDA runtime.");
    break;
  case cudaErrorInvalidKernelImage:
    fprintf(stderr, "This indicates that the device kernel image is invalid.");
    break;
  case cudaErrorDeviceUninitialized:
    fprintf(stderr, "This most frequently indicates that there is no context bound to the current thread. This can also be returned if the context passed to an API call is not a valid handle (such as a context that has had cuCtxDestroy() invoked on it). This can also be returned if a user mixes different API versions (i.e. 3010 context with 3020 API calls). See cuCtxGetApiVersion() for more details.");
    break;
  case cudaErrorMapBufferObjectFailed:
    fprintf(stderr, "This indicates that the buffer object could not be mapped.");
    break;
  case cudaErrorUnmapBufferObjectFailed:
    fprintf(stderr, "This indicates that the buffer object could not be unmapped.");
    break;
  case cudaErrorArrayIsMapped:
    fprintf(stderr, "This indicates that the specified array is currently mapped and thus cannot be destroyed.");
    break;
  case cudaErrorAlreadyMapped:
    fprintf(stderr, "This indicates that the resource is already mapped.");
    break;
  case cudaErrorNoKernelImageForDevice:
    fprintf(stderr, "This indicates that there is no kernel image available that is suitable for the device. This can occur when a user specifies code generation options for a particular CUDA source file that do not include the corresponding device configuration.");
    break;
  case cudaErrorAlreadyAcquired:
    fprintf(stderr, "This indicates that a resource has already been acquired.");
    break;
  case cudaErrorNotMapped:
    fprintf(stderr, "This indicates that a resource is not mapped.");
    break;
  case cudaErrorNotMappedAsArray:
    fprintf(stderr, "This indicates that a mapped resource is not available for access as an array.");
    break;
  case cudaErrorNotMappedAsPointer:
    fprintf(stderr, "This indicates that a mapped resource is not available for access as a pointer.");
    break;
  case cudaErrorECCUncorrectable:
    fprintf(stderr, "This indicates that an uncorrectable ECC error was detected during execution.");
    break;
  case cudaErrorUnsupportedLimit:
    fprintf(stderr, "This indicates that the cudaLimit passed to the API call is not supported by the active device.");
    break;
  case cudaErrorDeviceAlreadyInUse:
    fprintf(stderr, "This indicates that a call tried to access an exclusive-thread device that is already in use by a different thread.");
    break;
  case cudaErrorPeerAccessUnsupported:
    fprintf(stderr, "This error indicates that P2P access is not supported across the given devices.");
    break;
  case cudaErrorInvalidPtx:
    fprintf(stderr, "A PTX compilation failed. The runtime may fall back to compiling PTX if an application does not contain a suitable binary for the current device.");
    break;
  case cudaErrorInvalidGraphicsContext:
    fprintf(stderr, "This indicates an error with the OpenGL or DirectX context.");
    break;
  case cudaErrorNvlinkUncorrectable:
    fprintf(stderr, "This indicates that an uncorrectable NVLink error was detected during the execution.");
    break;
  case cudaErrorJitCompilerNotFound:
    fprintf(stderr, "This indicates that the PTX JIT compiler library was not found. The JIT Compiler library is used for PTX compilation. The runtime may fall back to compiling PTX if an application does not contain a suitable binary for the current device.");
    break;
  case cudaErrorInvalidSource:
    fprintf(stderr, "This indicates that the device kernel source is invalid.");
    break;
  case cudaErrorFileNotFound:
    fprintf(stderr, "This indicates that the file specified was not found.");
    break;
  case cudaErrorSharedObjectSymbolNotFound:
    fprintf(stderr, "This indicates that a link to a shared object failed to resolve.");
    break;
  case cudaErrorSharedObjectInitFailed:
    fprintf(stderr, "This indicates that initialization of a shared object failed.");
    break;
  case cudaErrorOperatingSystem:
    fprintf(stderr, "This error indicates that an OS call failed.");
    break;
  case cudaErrorInvalidResourceHandle:
    fprintf(stderr, "This indicates that a resource handle passed to the API call was not valid. Resource handles are opaque types like cudaStream_t and cudaEvent_t.");
    break;
  case cudaErrorIllegalState:
    fprintf(stderr, "This indicates that a resource required by the API call is not in a valid state to perform the requested operation.");
    break;
  case cudaErrorSymbolNotFound:
    fprintf(stderr, "This indicates that a named symbol was not found. Examples of symbols are global/constant variable names, texture names, and surface names.");
    break;
  case cudaErrorNotReady:
    fprintf(stderr, "This indicates that asynchronous operations issued previously have not completed yet. This result is not actually an error, but must be indicated differently than cudaSuccess (which indicates completion). Calls that may return this value include cudaEventQuery() and cudaStreamQuery().");
    break;
  case cudaErrorIllegalAddress:
    fprintf(stderr, "The device encountered a load or store instruction on an invalid memory address. This leaves the process in an inconsistent state and any further CUDA work will return the same error. To continue using CUDA, the process must be terminated and relaunched.");
    break;
  case cudaErrorLaunchOutOfResources:
    fprintf(stderr, "This indicates that a launch did not occur because it did not have appropriate resources. Although this error is similar to cudaErrorInvalidConfiguration, this error usually indicates that the user has attempted to pass too many arguments to the device kernel, or the kernel launch specifies too many threads for the kernel's register count.");
    break;
  case cudaErrorLaunchTimeout:
    fprintf(stderr, "This indicates that the device kernel took too long to execute. This can only occur if timeouts are enabled - see the device property kernelExecTimeoutEnabled for more information. This leaves the process in an inconsistent state and any further CUDA work will return the same error. To continue using CUDA, the process must be terminated and relaunched.");
    break;
  case cudaErrorLaunchIncompatibleTexturing:
    fprintf(stderr, "This error indicates a kernel launch that uses an incompatible texturing mode.");
    break;
  case cudaErrorPeerAccessAlreadyEnabled:
    fprintf(stderr, "This error indicates that a call to cudaDeviceEnablePeerAccess() is trying to re-enable peer addressing on from a context which has already had peer addressing enabled.");
    break;
  case cudaErrorPeerAccessNotEnabled:
    fprintf(stderr, "This error indicates that cudaDeviceDisablePeerAccess() is trying to disable peer addressing which has not been enabled yet via cudaDeviceEnablePeerAccess().");
    break;
  case cudaErrorSetOnActiveProcess:
    fprintf(stderr, "This indicates that the user has called cudaSetValidDevices(), cudaSetDeviceFlags(), cudaD3D9SetDirect3DDevice(), cudaD3D10SetDirect3DDevice, cudaD3D11SetDirect3DDevice(), or cudaVDPAUSetVDPAUDevice() after initializing the CUDA runtime by calling non-device management operations (allocating memory and launching kernels are examples of non-device management operations). This error can also be returned if using runtime/driver interoperability and there is an existing CUcontext active on the host thread.");
    break;
  case cudaErrorContextIsDestroyed:
    fprintf(stderr, "This error indicates that the context current to the calling thread has been destroyed using cuCtxDestroy, or is a primary context which has not yet been initialized.");
    break;
  case cudaErrorAssert:
    fprintf(stderr, "An assert triggered in device code during kernel execution. The device cannot be used again. All existing allocations are invalid. To continue using CUDA, the process must be terminated and relaunched.");
    break;
  case cudaErrorTooManyPeers:
    fprintf(stderr, "This error indicates that the hardware resources required to enable peer access have been exhausted for one or more of the devices passed to cudaEnablePeerAccess().");
    break;
  case cudaErrorHostMemoryAlreadyRegistered:
    fprintf(stderr, "This error indicates that the memory range passed to cudaHostRegister() has already been registered.");
    break;
  case cudaErrorHostMemoryNotRegistered:
    fprintf(stderr, "This error indicates that the pointer passed to cudaHostUnregister() does not correspond to any currently registered memory region.");
    break;
  case cudaErrorHardwareStackError:
    fprintf(stderr, "Device encountered an error in the call stack during kernel execution, possibly due to stack corruption or exceeding the stack size limit. This leaves the process in an inconsistent state and any further CUDA work will return the same error. To continue using CUDA, the process must be terminated and relaunched.");
    break;
  case cudaErrorIllegalInstruction:
    fprintf(stderr, "The device encountered an illegal instruction during kernel execution This leaves the process in an inconsistent state and any further CUDA work will return the same error. To continue using CUDA, the process must be terminated and relaunched.");
    break;
  case cudaErrorMisalignedAddress:
    fprintf(stderr, "The device encountered a load or store instruction on a memory address which is not aligned. This leaves the process in an inconsistent state and any further CUDA work will return the same error. To continue using CUDA, the process must be terminated and relaunched.");
    break;
  case cudaErrorInvalidAddressSpace:
    fprintf(stderr, "While executing a kernel, the device encountered an instruction which can only operate on memory locations in certain address spaces (global, shared, or local), but was supplied a memory address not belonging to an allowed address space. This leaves the process in an inconsistent state and any further CUDA work will return the same error. To continue using CUDA, the process must be terminated and relaunched.");
    break;
  case cudaErrorInvalidPc:
    fprintf(stderr, "The device encountered an invalid program counter. This leaves the process in an inconsistent state and any further CUDA work will return the same error. To continue using CUDA, the process must be terminated and relaunched.");
    break;
  case cudaErrorLaunchFailure:
    fprintf(stderr, "An exception occurred on the device while executing a kernel. Common causes include dereferencing an invalid device pointer and accessing out of bounds shared memory. Less common cases can be system specific - more information about these cases can be found in the system specific user guide. This leaves the process in an inconsistent state and any further CUDA work will return the same error. To continue using CUDA, the process must be terminated and relaunched.");
    break;
  case cudaErrorCooperativeLaunchTooLarge:
    fprintf(stderr, "This error indicates that the number of blocks launched per grid for a kernel that was launched via either cudaLaunchCooperativeKernel or cudaLaunchCooperativeKernelMultiDevice exceeds the maximum number of blocks as allowed by cudaOccupancyMaxActiveBlocksPerMultiprocessor or cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags times the number of multiprocessors as specified by the device attribute cudaDevAttrMultiProcessorCount.");
    break;
  case cudaErrorNotPermitted:
    fprintf(stderr, "This error indicates the attempted operation is not permitted.");
    break;
  case cudaErrorNotSupported:
    fprintf(stderr, "This error indicates the attempted operation is not supported on the current system or device.");
    break;
  case cudaErrorSystemNotReady:
    fprintf(stderr, "This error indicates that the system is not yet ready to start any CUDA work. To continue using CUDA, verify the system configuration is in a valid state and all required driver daemons are actively running. More information about this error can be found in the system specific user guide.");
    break;
  case cudaErrorSystemDriverMismatch:
    fprintf(stderr, "This error indicates that there is a mismatch between the versions of the display driver and the CUDA driver. Refer to the compatibility documentation for supported versions.");
    break;
  case cudaErrorCompatNotSupportedOnDevice:
    fprintf(stderr, "This error indicates that the system was upgraded to run with forward compatibility but the visible hardware detected by CUDA does not support this configuration. Refer to the compatibility documentation for the supported hardware matrix or ensure that only supported hardware is visible during initialization via the CUDA_VISIBLE_DEVICES environment variable.");
    break;
  case cudaErrorStreamCaptureUnsupported:
    fprintf(stderr, "The operation is not permitted when the stream is capturing.");
    break;
  case cudaErrorStreamCaptureInvalidated:
    fprintf(stderr, "The current capture sequence on the stream has been invalidated due to a previous error.");
    break;
  case cudaErrorStreamCaptureMerge:
    fprintf(stderr, "The operation would have resulted in a merge of two independent capture sequences.");
    break;
  case cudaErrorStreamCaptureUnmatched:
    fprintf(stderr, "The capture was not initiated in this stream.");
    break;
  case cudaErrorStreamCaptureUnjoined:
    fprintf(stderr, "The capture sequence contains a fork that was not joined to the primary stream.");
    break;
  case cudaErrorStreamCaptureIsolation:
    fprintf(stderr, "A dependency would have been created which crosses the capture sequence boundary. Only implicit in-stream ordering dependencies are allowed to cross the boundary.");
    break;
  case cudaErrorStreamCaptureImplicit:
    fprintf(stderr, "The operation would have resulted in a disallowed implicit dependency on a current capture sequence from cudaStreamLegacy.");
    break;
  case cudaErrorCapturedEvent:
    fprintf(stderr, "The operation is not permitted on an event which was last recorded in a capturing stream.");
    break;
  case cudaErrorStreamCaptureWrongThread:
    fprintf(stderr, "A stream capture sequence not initiated with the cudaStreamCaptureModeRelaxed argument to cudaStreamBeginCapture was passed to cudaStreamEndCapture in a different thread.");
    break;
  case cudaErrorTimeout:
    fprintf(stderr, "This indicates that the wait operation has timed out.");
    break;
  case cudaErrorGraphExecUpdateFailure:
    fprintf(stderr, "This error indicates that the graph update was not performed because it included changes which violated constraints specific to instantiated graph update.");
    break;
  case cudaErrorUnknown:
    fprintf(stderr, "This indicates that an unknown internal error has occurred.");
    break;
  default:
    fprintf(stderr, "Unknown");
    break;
  }
  fprintf(stderr, "\n");
  throw error;
}
