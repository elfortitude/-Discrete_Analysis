using UnityEngine;
using UnityEditor;
public class MoveBackground : MonoBehaviour
{
    public float speed = 1.0f;
    public GameObject water;
    void FixedUpdate()
    {
        transform.Translate(Vector3.down * speed * Time.deltaTime);

        if (transform.position.y < -17f)
        {
            Instantiate(water, new Vector3(0, 25.17f, 10), Quaternion.identity);
            Destroy(gameObject);
        }
    }
}
