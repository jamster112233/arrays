#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
long getCombinations(vector<int> const&, vector<int> const&, int max_val);
long getArrayPairs(int, int, vector<int> const&);

long getCombinations(vector<int> const &l_arr, vector<int> const &r_arr, int max_val){
    long last_i = 0;
    long l_up_i = 0;
    long r_up_i = r_arr.size();
    long combos = 0;

    while(l_up_i < l_arr.size() && r_up_i > 0){
        // search for next unique value in left portion
        auto l_up = upper_bound(l_arr.begin(), l_arr.end(), l_arr[last_i]);
        l_up_i = (l_up == l_arr.end()) ? l_arr.size() : l_up - l_arr.begin();

        // search for index meeting multiplication criterion in right (round down)
        int search_v = max_val/l_arr[last_i];
        auto r_up = upper_bound(r_arr.begin(), r_arr.end(), search_v);

        if(r_up == r_arr.end()){
            // value not found or end of array?
            if(r_arr[0] > search_v){
                r_up_i = 0;
            } else {
                r_up_i = r_arr.size();
            }
        } else {
            r_up_i = r_up - r_arr.begin();
        }

        combos += r_up_i * (l_up_i - last_i);
        last_i = l_up_i;
    }
    return combos;
}

// start of segment, end of segment
long getArrayPairs(int left, int right, vector<int> const &arr){
    if(left >= right)
        return 0;

    int max_i = 0;
    int max_val = 0;
    long combos = 0;
    float mid_i = (left+right)/2;

    // find optimal max val
    for(int max_it = left; max_it < right; max_it++){
        if((arr[max_it] > max_val) || (arr[max_it] == max_val && abs(mid_i - (float)max_it) <= abs(mid_i - (float)max_i))){
            max_i = max_it;
            max_val = arr[max_it];
        }
    }

    vector<int> l_arr(arr.begin()+left, arr.begin()+max_i);
    vector<int> r_arr(arr.begin()+max_i+1, arr.begin()+right);

    sort(l_arr.begin(), l_arr.end());
    sort(r_arr.begin(), r_arr.end());

    combos += getCombinations(l_arr, r_arr, max_val);
    combos += getCombinations(l_arr, vector<int> (arr.begin()+max_i, arr.begin()+max_i+1),max_val);
    combos += getCombinations(vector<int> (arr.begin()+max_i, arr.begin()+max_i+1), r_arr,max_val);

    // do not include max_i
    long left_result = getArrayPairs(left, max_i, arr);
    long right_result = getArrayPairs(max_i+1, right, arr);

    return combos + left_result + right_result;
}


// Complete the solve function below.
long solve(vector<int> arr) {
    return getArrayPairs(0, arr.size(), arr);
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    int arr_count;
    cin >> arr_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(arr_count);

    for (int i = 0; i < arr_count; i++) {
        int arr_item = stoi(arr_temp[i]);
        arr[i] = arr_item;
    }

    long result = solve(arr);

    cout << result << "\n";

    // fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
