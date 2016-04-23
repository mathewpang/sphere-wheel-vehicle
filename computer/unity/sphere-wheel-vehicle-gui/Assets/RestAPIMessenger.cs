using UnityEngine;
using System.Collections;

public class RestAPIMessenger : MonoBehaviour {

    string url = "";
    int prev_radius;
    int prev_angle;
	// Use this for initialization
	void Start () {
        url = "localhost:8000";
        prev_radius = -1;
        prev_angle = -1;
        //url = "192.168.0.102:8000";
    }
	
	// Update is called once per frame
	void Update () {
	
	}

    public void emergencyStop()
    {
        sendMessage(0, 0);
    }

    public void sendMessage(int radius, int angle)
    {
        if(radius != prev_radius || angle != prev_angle)
        {
            WWWForm radius_form = new WWWForm();
            WWWForm angle_form = new WWWForm();
            radius_form.AddField("Radius", radius.ToString());
            angle_form.AddField("Angle", angle.ToString());
            WWW www_rad = new WWW(url, radius_form);
            WWW www_ang = new WWW(url, angle_form);
            //  StartCoroutine(WaitForRequest(www));
            prev_radius = radius;
            prev_angle = angle;
        }
    }

    public void sendAngle(int angle)
    {
        if (angle != prev_angle)
        {
            WWWForm angle_form = new WWWForm();
            angle_form.AddField("Angle", angle.ToString());
            WWW www_ang = new WWW(url, angle_form);
            //  StartCoroutine(WaitForRequest(www));
            prev_angle = angle;
        }
    }


    public void sendRadius(int radius)
    {
        if (radius != prev_radius )
        {
            WWWForm radius_form = new WWWForm();
            radius_form.AddField("Radius", radius.ToString());
            WWW www_rad = new WWW(url, radius_form);
            //  StartCoroutine(WaitForRequest(www));
            prev_radius = radius;
        }
    }

    public void sendRadius(string str_radius)
    {
        print(str_radius);
        int radius_int = System.Int32.Parse(str_radius);
        sendRadius(radius_int);
    }

    IEnumerator WaitForRequest(WWW www)
    {
        yield return www;
     // check for errors
     if (www.error == null)
        {
            Debug.Log("WWW Ok!: " + www.data);
        }
        else
        {
            Debug.Log("WWW Error: " + www.error);
        }
    }

    private bool isRadiusRoughlyEqual(int radius)
    {
        if (Mathf.Abs(radius - prev_radius) > 0)
        {
            return false;
        }
        return true;
    }
    private bool isAngleRoughlyEqual(int angle)
    {
        if(Mathf.Abs(angle - prev_angle) > 0)
        {
            return false;
        }
        return true;
    }
}
