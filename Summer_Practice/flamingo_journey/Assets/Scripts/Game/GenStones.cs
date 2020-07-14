using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenStones : MonoBehaviour
{
    public GameObject[] stones;
    void Start()
    {
        StartCoroutine(gen());
    }
    IEnumerator gen()
    {
        Quaternion spawnRotation = Quaternion.identity;
        while (true)
        {
            Instantiate(
                stones[Random.Range(0, stones.Length)],
                new Vector3(Random.Range(-2.35f, 2.35f), 6f, 0),
                Quaternion.identity
            );
            yield return new WaitForSeconds(2.5f);
        }
    }
}
