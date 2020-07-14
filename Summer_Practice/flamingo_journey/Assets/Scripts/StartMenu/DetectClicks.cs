using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class DetectClicks : MonoBehaviour
{
    public Text gameName;
    public Image mainImage, handImage;
    private bool clicked;
    void OnMouseDown () {
        if (!clicked) {
            clicked = true;
            gameName.GetComponent <Animation> ().Play ("GameNameAnimation");
            mainImage.GetComponent <Animation> ().Play ("MainFlamingoAnimation");
            handImage.GetComponent <Animation> ().Play ("HandAnimation2");
            Invoke("LaunchScene", 2.0f);
            //gameName.text.SetActive (false);
        }
        //gameName.gameObject.SetActive (false);
        //mainImage.gameObject.SetActive (false);
        //handImage.gameObject.SetActive (false);
    }

    void LaunchScene () {
        SceneManager.LoadScene("GameScene");
    }
}
