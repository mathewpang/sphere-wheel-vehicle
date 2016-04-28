using UnityEngine;
using System.Collections;

public class camera : MonoBehaviour {

    public Renderer renderer;
    public CanvasRenderer canvRenderer;
    Texture2D texture;
    public GameObject go;
    // Use this for initialization
    string url = "http://192.168.100.57:8091/static_simple.html";
    string url2 = "http://192.168.0.102:8091/?action=snapshot";

    void Start () {
        
        texture = new Texture2D(4, 4, TextureFormat.DXT1, false);
        canvRenderer = GetComponent<CanvasRenderer>();
    }
	
	// Update is called once per frame
	void Update () {
        // Start a download of the given URL
        StartCoroutine(LoadImage());
    }

    IEnumerator LoadImage()
    {
        WWW www = new WWW(url2);
        yield return www;
        //renderer.material.mainTexture = www.texture;
        //image script material = sprite- default material
        renderer = GetComponent<Renderer>();
        canvRenderer = GetComponent<CanvasRenderer>();
        canvRenderer.SetMaterial(canvRenderer.GetMaterial(), www.texture);
        //renderer.material.mainTexture = www.texture;
    }
}

