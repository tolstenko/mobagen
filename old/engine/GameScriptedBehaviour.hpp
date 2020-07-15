#pragma once
#include "Behaviour.hpp"

namespace mobagen {
  class GameScriptedBehaviour : public Behaviour {
  public:
//  runInEditMode	Allow a specific instance of a MonoBehaviour to run in edit mode (only available in the editor).
//  useGUILayout	Disabling this lets you skip the GUI layout phase.

//  CancelInvoke	Cancels all Invoke calls on this MonoBehaviour.
//  Invoke	Invokes the method methodName in time seconds.
//  InvokeRepeating	Invokes the method methodName in time seconds, then repeatedly every repeatRate seconds.
//  IsInvoking	Is any invoke on methodName pending?
//  StartCoroutine	Starts a coroutine.
//  StopAllCoroutines	Stops all coroutines running on this behaviour.
//  StopCoroutine	Stops the first coroutine named methodName, or the coroutine stored in routine running on this behaviour.

//  print	Logs message to the Unity Console (identical to Debug.Log).

    /// @brief Awake is called when the script instance is being loaded.
    virtual void Awake() {};
//  FixedUpdate	This function is called every fixed framerate frame, if the MonoBehaviour is enabled.
//  LateUpdate	LateUpdate is called every frame, if the Behaviour is enabled.
//  OnAnimatorIK	Callback for setting up animation IK (inverse kinematics).
//  OnAnimatorMove	Callback for processing animation movements for modifying root motion.
//  OnApplicationFocus	Sent to all GameObjects when the player gets or loses focus.
//  OnApplicationPause	Sent to all GameObjects when the application pauses.
//  OnApplicationQuit	Sent to all game objects before the application is quit.
//  OnAudioFilterRead	If OnAudioFilterRead is implemented, Unity will insert a custom filter into the audio DSP chain.
//  OnBecameInvisible	OnBecameInvisible is called when the renderer is no longer visible by any camera.
//  OnBecameVisible	OnBecameVisible is called when the renderer became visible by any camera.
//  OnCollisionEnter	OnCollisionEnter is called when this collider/rigidbody has begun touching another rigidbody/collider.
//  OnCollisionEnter2D	Sent when an incoming collider makes contact with this object's collider (2D physics only).
//  OnCollisionExit	OnCollisionExit is called when this collider/rigidbody has stopped touching another rigidbody/collider.
//  OnCollisionExit2D	Sent when a collider on another object stops touching this object's collider (2D physics only).
//  OnCollisionStay	OnCollisionStay is called once per frame for every collider/rigidbody that is touching rigidbody/collider.
//  OnCollisionStay2D	Sent each frame where a collider on another object is touching this object's collider (2D physics only).
//  OnConnectedToServer	Called on the client when you have successfully connected to a server.
//  OnControllerColliderHit	OnControllerColliderHit is called when the controller hits a collider while performing a Move.
//  OnDestroy	This function is called when the MonoBehaviour will be destroyed.
//  OnDisable	This function is called when the behaviour becomes disabled () or inactive.
//  OnDisconnectedFromServer	Called on the client when the connection was lost or you disconnected from the server.
//  OnDrawGizmos	Implement OnDrawGizmos if you want to draw gizmos that are also pickable and always drawn.
//  OnDrawGizmosSelected	Implement OnDrawGizmosSelected to draw a gizmo if the object is selected.
//  OnEnable	This function is called when the object becomes enabled and active.
//  OnFailedToConnect	Called on the client when a connection attempt fails for some reason.
//  OnFailedToConnectToMasterServer	Called on clients or servers when there is a problem connecting to the MasterServer.

    /// @brief OnGUI is called for rendering and handling GUI events.
    virtual void OnGUI() {};

//  OnJointBreak	Called when a joint attached to the same game object broke.
//  OnJointBreak2D	Called when a Joint2D attached to the same game object breaks.
//  OnMasterServerEvent	Called on clients or servers when reporting events from the MasterServer.
//  OnMouseDown	OnMouseDown is called when the user has pressed the mouse button while over the GUIElement or Collider.
//  OnMouseDrag	OnMouseDrag is called when the user has clicked on a GUIElement or Collider and is still holding down the mouse.
//  OnMouseEnter	Called when the mouse enters the GUIElement or Collider.
//  OnMouseExit	Called when the mouse is not any longer over the GUIElement or Collider.
//  OnMouseOver	Called every frame while the mouse is over the GUIElement or Collider.
//  OnMouseUp	OnMouseUp is called when the user has released the mouse button.
//  OnMouseUpAsButton	OnMouseUpAsButton is only called when the mouse is released over the same GUIElement or Collider as it was pressed.
//  OnNetworkInstantiate	Called on objects which have been network instantiated with Network.Instantiate.
//  OnParticleCollision	OnParticleCollision is called when a particle hits a Collider.
//  OnParticleTrigger	OnParticleTrigger is called when any particles in a particle system meet the conditions in the trigger module.
//  OnPlayerConnected	Called on the server whenever a new player has successfully connected.
//  OnPlayerDisconnected	Called on the server whenever a player disconnected from the server.
//  OnPostRender	OnPostRender is called after a camera finished rendering the scene.
//  OnPreCull	OnPreCull is called before a camera culls the scene.
//  OnPreRender	OnPreRender is called before a camera starts rendering the scene.
//  OnRenderImage	OnRenderImage is called after all rendering is complete to render image.
//  OnRenderObject	OnRenderObject is called after camera has rendered the scene.
//  OnSerializeNetworkView	Used to customize synchronization of variables in a script watched by a network view.
//  OnServerInitialized	Called on the server whenever a Network.InitializeServer was invoked and has completed.
//  OnTransformChildrenChanged	This function is called when the list of children of the transform of the GameObject has changed.
//  OnTransformParentChanged	This function is called when the parent property of the transform of the GameObject has changed.
//  OnTriggerEnter	OnTriggerEnter is called when the Collider other enters the trigger.
//  OnTriggerEnter2D	Sent when another object enters a trigger collider attached to this object (2D physics only).
//  OnTriggerExit	OnTriggerExit is called when the Collider other has stopped touching the trigger.
//  OnTriggerExit2D	Sent when another object leaves a trigger collider attached to this object (2D physics only).
//  OnTriggerStay	OnTriggerStay is called once per frame for every Collider other that is touching the trigger.
//  OnTriggerStay2D	Sent each frame where another object is within a trigger collider attached to this object (2D physics only).
//  OnValidate	This function is called when the script is loaded or a value is changed in the inspector (Called in the editor only).
//  OnWillRenderObject	OnWillRenderObject is called for each camera if the object is visible and not a UI element.
//  Reset	Reset to default values.
    /// @brief Start is called on the frame when a script is enabled just before any of the Update methods is called the first time.
    virtual void Start() {};

    /// @brief Update is called every frame, if the MonoBehaviour is enabled.
    virtual void Update() {};
  };
}