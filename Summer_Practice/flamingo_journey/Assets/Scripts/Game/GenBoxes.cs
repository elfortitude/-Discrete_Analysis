using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenBoxes : MonoBehaviour
{
    public GameObject[] boxes;
    void Start()
    {
        StartCoroutine(genB());
    }

    IEnumerator genB()
    {
        while(true) {
            Instantiate(
                boxes[Random.Range(0, boxes.Length)],
                new Vector3(Random.Range(-2.35f, 2.35f), Random.Range(-4.35f, 4.35f), 5),
                Quaternion.identity);
            yield return new WaitForSeconds(5f);
        }
    }
}
