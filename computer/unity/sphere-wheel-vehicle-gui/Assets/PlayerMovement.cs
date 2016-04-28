using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class PlayerMovement : MonoBehaviour {
		private Vector3 movementVector;
		private CharacterController characterController;
		private float gravity = 40;
		private double radius;
		private double angle;
		public RestAPIMessenger Control;
		public Text GUIRadius;
		public Text GUIAngle;
		

		
	void Start()
	{	
		characterController = GetComponent<CharacterController>();
	}
	
	
	void Update()
	{
		movementVector.x = Input.GetAxis("LeftJoystickX");
		movementVector.z = Input.GetAxis("LeftJoystickY"); 
		radius = (Mathf.Sqrt(Mathf.Pow(movementVector.x,2) + Mathf.Pow(movementVector.z,2))) * 127;
		angle = (Mathf.Atan(movementVector.x/movementVector.z))* (180/Mathf.PI);
		Debug.Log(angle);
		
		if (radius < 40)
		{	
			Control.emergencyStop();
		}
		else
		{
			Control.sendRadius(radius);
		}
		
		
		if(characterController.isGrounded)
		{
		movementVector.y = 0;
		}
	
		//guiText = GameObject.Find("RADIUS").GetComponent<Text>();
		GUIRadius.GetComponent<Text>().text = radius.ToString("F4");
		GUIAngle.GetComponent<Text>().text = angle.ToString("F1");
		movementVector.y -= gravity * Time.deltaTime;
	
			characterController.Move(movementVector * Time.deltaTime);
	}
		
	}
	
