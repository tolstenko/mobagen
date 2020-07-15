#pragma once
#include "GameBehaviour.hpp"

namespace mobagen {
/// \brief A Camera is a device through which the player views the world.
///  A screen space point is defined in pixels. The bottom-left of the screen is (0,0); the right-top is (pixelWidth,pixelHeight). The z position is in world units from the Camera.
///  A viewport space point is normalized and relative to the Camera. The bottom-left of the Camera is (0,0); the top-right is (1,1). The z position is in world units from the Camera.
///  A world space point is defined in global coordinates (for example, Transform.position).
  class GameCamera : public GameBehaviour {
//  Description
//      A Camera is a device through which the player views the world.
//
//  Static Properties
//  allCameras	Returns all enabled cameras in the scene.
//  allCamerasCount	The number of cameras in the current scene.
//  current	The camera we are currently rendering with, for low-level render control only (Read Only).
//  main	The first enabled camera tagged "MainCamera" (Read Only).
//  onPostRender	Event that is fired after any camera finishes rendering.
//  onPreCull	Event that is fired before any camera starts culling.
//  onPreRender	Event that is fired before any camera starts rendering.


//  Properties
//  activeTexture	Gets the temporary RenderTexture target for this Camera.
//  actualRenderingPath	The rendering path that is currently being used (Read Only).
//  allowDynamicResolution	Dynamic Resolution Scaling.
//  allowHDR	High dynamic range rendering.
//  allowMSAA	MSAA rendering.
//  areVRStereoViewMatricesWithinSingleCullTolerance	Determines whether the stereo view matrices are suitable to allow for a single pass cull.
//  aspect	The aspect ratio (width divided by height).
//  backgroundColor	The color with which the screen will be cleared.
//  cameraToWorldMatrix	Matrix that transforms from camera space to world space (Read Only).
//  cameraType	Identifies what kind of camera this is.
//  clearFlags	How the camera clears the background.
//  clearStencilAfterLightingPass	Should the camera clear the stencil buffer after the deferred light pass?
//  commandBufferCount	Number of command buffers set up on this camera (Read Only).
//  cullingMask	This is used to render parts of the scene selectively.
//  cullingMatrix	Sets a custom matrix for the camera to use for all culling queries.
//  depth	Camera's depth in the camera rendering order.
//  depthTextureMode	How and if camera generates a depth texture.
//  eventMask	Mask to select which layers can trigger events on the camera.
//  farClipPlane	The far clipping plane distance.
//  fieldOfView	The field of view of the camera in degrees.
//  forceIntoRenderTexture	Should camera rendering be forced into a RenderTexture.
//  layerCullDistances	Per-layer culling distances.
//  layerCullSpherical	How to perform per-layer culling for a Camera.
//  nearClipPlane	The near clipping plane distance.
//  nonJitteredProjectionMatrix	Get or set the raw projection matrix with no camera offset (no jittering).
//  opaqueSortMode	Opaque object sorting mode.
//  orthographic	Is the camera orthographic (true) or perspective (false)?
//  orthographicSize	Camera's half-size when in orthographic mode.
//  pixelHeight	How tall is the camera in pixels (not accounting for dynamic resolution scaling) (Read Only).
//  pixelRect	Where on the screen is the camera rendered in pixel coordinates.
//  pixelWidth	How wide is the camera in pixels (not accounting for dynamic resolution scaling) (Read Only).
//  previousViewProjectionMatrix	Get the view projection matrix used on the last frame.
//  projectionMatrix	Set a custom projection matrix.
//  rect	Where on the screen is the camera rendered in normalized coordinates.
//  renderingPath	The rendering path that should be used, if possible.
//  scaledPixelHeight	How tall is the camera in pixels (accounting for dynamic resolution scaling) (Read Only).
//  scaledPixelWidth	How wide is the camera in pixels (accounting for dynamic resolution scaling) (Read Only).
//  scene	If not null, the camera will only render the contents of the specified scene.
//  stereoActiveEye	Returns the eye that is currently rendering. If called when stereo is not enabled it will return Camera.MonoOrStereoscopicEye.Mono. If called during a camera rendering callback such as OnRenderImage it will return the currently rendering eye. If called outside of a rendering callback and stereo is enabled, it will return the default eye which is Camera.MonoOrStereoscopicEye.Left.
//  stereoConvergence	Distance to a point where virtual eyes converge.
//  stereoEnabled	Stereoscopic rendering.
//  stereoSeparation	The distance between the virtual eyes. Use this to query or set the current eye separation. Note that most VR devices provide this value, in which case setting the value will have no effect.
//  stereoTargetEye	Defines which eye of a VR display the Camera renders into.
//  targetDisplay	Set the target display for this Camera.
//  targetTexture	Destination render texture.
//  transparencySortAxis	An axis that describes the direction along which the distances of objects are measured for the purpose of sorting.
//  transparencySortMode	Transparent object sorting mode.
//  useJitteredProjectionMatrixForTransparentRendering	Should the jittered matrix be used for transparency rendering?
//  useOcclusionCulling	Whether or not the Camera will use occlusion culling during rendering.
//  velocity	Get the world-space speed of the camera (Read Only).
//  worldToCameraMatrix	Matrix that transforms from world to camera space.


//  Public Methods
//  AddCommandBuffer	Add a command buffer to be executed at a specified place.
//  CalculateFrustumCorners	Given viewport coordinates, calculates the view space vectors pointing to the four frustum corners at the specified camera depth.
//  CalculateObliqueMatrix	Calculates and returns oblique near-plane projection matrix.
//  CopyFrom	Makes this camera's settings match other camera.
//  CopyStereoDeviceProjectionMatrixToNonJittered	Sets the non-jittered projection matrix, sourced from the VR SDK.
//  GetCommandBuffers	Get command buffers to be executed at a specified place.
//  GetStereoNonJitteredProjectionMatrix	Gets the non-jittered projection matrix of a specific left or right stereoscopic eye.
//  GetStereoProjectionMatrix	Gets the projection matrix of a specific left or right stereoscopic eye.
//  GetStereoViewMatrix	Gets the left or right view matrix of a specific stereoscopic eye.
//  RemoveAllCommandBuffers	Remove all command buffers set on this camera.
//  RemoveCommandBuffer	Remove command buffer from execution at a specified place.
//  RemoveCommandBuffers	Remove command buffers from execution at a specified place.
//  Render	Render the camera manually.
//  RenderToCubemap	Render into a static cubemap from this camera.
//  RenderWithShader	Render the camera with shader replacement.
//  ResetAspect	Revert the aspect ratio to the screen's aspect ratio.
//  ResetCullingMatrix	Make culling queries reflect the camera's built in parameters.
//  ResetProjectionMatrix	Make the projection reflect normal camera's parameters.
//  ResetReplacementShader	Remove shader replacement from camera.
//  ResetStereoProjectionMatrices	Reset the camera to using the Unity computed projection matrices for all stereoscopic eyes.
//  ResetStereoViewMatrices	Reset the camera to using the Unity computed view matrices for all stereoscopic eyes.
//  ResetTransparencySortSettings	Resets this Camera's transparency sort settings to the default. Default transparency settings are taken from GraphicsSettings instead of directly from this Camera.
//  ResetWorldToCameraMatrix	Make the rendering position reflect the camera's position in the scene.
//  ScreenPointToRay	Returns a ray going from camera through a screen point.
//  ScreenToViewportPoint	Transforms position from screen space into viewport space.
//  ScreenToWorldPoint	Transforms position from screen space into world space.
//  SetReplacementShader	Make the camera render with shader replacement.
//  SetStereoProjectionMatrix	Sets a custom projection matrix for a specific stereoscopic eye.
//  SetStereoViewMatrix	Sets a custom view matrix for a specific stereoscopic eye.
//  SetTargetBuffers	Sets the Camera to render to the chosen buffers of one or more RenderTextures.
//  ViewportPointToRay	Returns a ray going from camera through a viewport point.
//  ViewportToScreenPoint	Transforms position from viewport space into screen space.
//  ViewportToWorldPoint	Transforms position from viewport space into world space.
//  WorldToScreenPoint	Transforms position from world space into screen space.
//  WorldToViewportPoint	Transforms position from world space into viewport space.
//
//
//  Static Methods
//  GetAllCameras	Fills an array of Camera with the current cameras in the scene, without allocating a new array.
//
//
//
// Messages
//  OnPostRender	OnPostRender is called after a camera has finished rendering the scene.
//  OnPreCull	OnPreCull is called before a camera culls the scene.
//  OnPreRender	OnPreRender is called before a camera starts rendering the scene.
//  OnRenderImage	OnRenderImage is called after all rendering is complete to render image.
//  OnRenderObject	OnRenderObject is called after camera has rendered the scene.
//  OnWillRenderObject	OnWillRenderObject is called for each camera if the object is visible.
//  Delegates
//      CameraCallback	Delegate type for camera callbacks.

  };
}