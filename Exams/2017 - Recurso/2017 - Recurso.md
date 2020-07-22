# Exame 2016/2017 - Recurso

1\. a) 

```cpp
int seq[n]; // Sequência
int vec[n] = {NULL}; // Número mínimo de subsequências em cada indíce

int f(int start) {
    if (vec[start] != NULL)
        return vec[start];

    if (start >= n)
        return 0;
    
    // Indíces das ocorrências do número na sequência
    vector<int> end = find_indexes_after(start, seq[start]);
    int minimum = ∞;
    
    for (index in end) {
        int temp = f(index + 1);

        if (temp < minimum)
            minimum = temp;
    }

    minimum += 1;
    
    vec[start] = minimum;
 
    return vec[start];
}
```

5\. a) 

**XPTO:** A G G T A C T A C C C C A

A G G T A C A C C C C A

A G G A C A C C C C A

A A G G A C A C C C C A

**OPTX:** A A G G A C A C C C C A 

A distância evolutiva é de 4.

&nbsp;&nbsp;&nbsp;&nbsp;b) 

| G | T | G | C | C |
|---|---|---|---|---|
| 0 | 0 | 1 | 0 | 0 |