using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveBoxes : MonoBehaviour
{
    public float speed = 1f;
    void FixedUpdate()
    {
        transform.Translate(Vector3.back * speed * Time.deltaTime);

        if (transform.position.z < -2)
            Destroy(gameObject);
    }
}
