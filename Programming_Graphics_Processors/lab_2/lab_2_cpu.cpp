#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>


using namespace std;
using namespace std::chrono;


#define GREY(x) 0.299*((float)((x)&255)) + 0.587*((float)(((x)>>8)&255)) + 0.114*((float)(((x)>>16)&255))




uint32_t tex2D(const vector<vector<uint32_t>>& vec, int32_t i, int32_t j){
    i = i < vec.size() ? i : vec.size() - 1;
    i = i < 0 ? 0 : i;

    j = j < vec[0].size() ? j : vec[0].size() - 1;
    j = j < 0 ? 0 : j;

    return vec[i][j];
}

void kernel_cpu(const vector<vector<uint32_t>>& g_text, vector<vector<uint32_t>>& d_data){
    for(int y = 0; y < g_text.size(); ++y){
        for(int x = 0; x < g_text[y].size(); ++x){
            uint32_t ans = 0;

			float	Gx, Gy, pixel;
			Gx = 0.0f;
			Gy = 0.0f;

			pixel = GREY(tex2D(g_text, x - 1, y - 1));
			Gx -= pixel;
			pixel = GREY(tex2D(g_text, x - 1, y));
			Gx -= pixel;
			pixel = GREY(tex2D(g_text, x - 1, y + 1));
			Gx -= pixel;
			pixel = GREY(tex2D(g_text, x + 1, y - 1));
			Gx += pixel;
			pixel = GREY(tex2D(g_text, x + 1, y));
			Gx += pixel;
			pixel = GREY(tex2D(g_text, x + 1, y + 1));
			Gx += pixel;

			pixel = GREY(tex2D(g_text, x - 1, y - 1));
			Gy -= pixel;
			pixel = GREY(tex2D(g_text, x, y - 1));
			Gy -= pixel;
			pixel = GREY(tex2D(g_text, x + 1, y - 1));
			Gy -= pixel;
			pixel = GREY(tex2D(g_text, x - 1, y + 1));
			Gy += pixel;
			pixel = GREY(tex2D(g_text, x, y + 1));
			Gy += pixel;
			pixel = GREY(tex2D(g_text, x + 1, y + 1));
			Gy += pixel;

            int32_t gradf = (int32_t)sqrt(Gx*Gx + Gy*Gy);
            // max(grad, 255)

            gradf = gradf > 255 ? 255 : gradf;
            // store values in variable for minimize work with global mem
            ans ^= (gradf << 16);
            ans ^= (gradf << 8);
            ans ^= (gradf);

            d_data[y][x] = ans;
        }
    }
}


int main(){
    string path;
    uint32_t w, h;
    cin >> path;
    ifstream fin(path);


    fin.read(reinterpret_cast<char*>(&w), sizeof(uint32_t));
    fin.read(reinterpret_cast<char*>(&h), sizeof(uint32_t));


    vector<vector<uint32_t>> img(h, vector<uint32_t>(w));
    vector<vector<uint32_t>> out(h, vector<uint32_t>(w));

    for(uint32_t i = 0; i < h; ++i){
        for(uint32_t j = 0; j < w; ++j){
            fin.read(reinterpret_cast<char*>(&img[i][j]), sizeof(uint32_t));
        }
    }
    ofstream fout("logs.log", ios::app);
    // timer:
    auto start = steady_clock::now();
    kernel_cpu(img, out);
    auto end = steady_clock::now();
    fout << "CPU" << endl;
    fout << h * w << endl;
    fout << ((double)duration_cast<microseconds>(end - start).count()) / 1000.0 << endl;
    fout.close();

    return 0;
}
