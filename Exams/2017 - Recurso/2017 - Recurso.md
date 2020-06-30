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