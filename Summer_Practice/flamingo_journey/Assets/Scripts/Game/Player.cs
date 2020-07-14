using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour
{
    public float speed = 3f;
    public static int score;
    void Update()
    {
        //Vector3 pos = Camera.main.ScreenToWorldPoint(Input.GetTouch(0).position);
        //transform.position = new Vector3(pos.x, transform.position.y, transform.position.z);

        float horizontal = Input.GetAxisRaw("Horizontal");
        float vertical = Input.GetAxisRaw("Vertical");

        Vector3 direction = new Vector3(horizontal, vertical, 0);
        transform.Translate(direction.normalized * Time.deltaTime * speed);
    }

    private void OnCollisionStay(Collision collision) {
        if (collision.gameObject.CompareTag("Stone"))
        {
            Destroy(gameObject);
            score = 0;
            SceneManager.LoadScene("FailScene");
        }
        if (collision.gameObject.CompareTag("box"))
        {
            Destroy(collision.gameObject);
            score += 1;
            print(score);
            if (score == 3)
            {
                Destroy(gameObject);
                score = 0;
                SceneManager.LoadScene("WinScene");
            }
        }
    }
}
