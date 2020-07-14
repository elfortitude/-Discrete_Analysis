using UnityEngine;

public class MoveObjects : MonoBehaviour
{
    public float speed = 1.5f;
    void FixedUpdate()
    {
        transform.Translate(Vector2.down * speed * Time.deltaTime);

        if (transform.position.y < -6f)
            Destroy(gameObject);
    }
}
