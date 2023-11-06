#include <bits/stdc++.h>

int main(){
    std::string nombre_ejecutable= "./gen.exe";
    std::string nombre_txt="texto.txt";
    
    std::string patron="OSTENTE";
    std::string rep="3";
    std::string sector="1";
    long repeticiones=30;
    long detencion=10000000000;
    long aumento=1000;
    long inicio=1000;
    for(long i=inicio;i<detencion;i+=aumento){
        std::string cant_char=std::to_string(i);
        for(long k=1;k<=10;k++){
            std::string comando = nombre_ejecutable + " " + nombre_txt + " " + cant_char + " " + patron + " " + rep + " " + std::to_string(k);   
            const char* comando_c = comando.c_str();
            int resultado = system(comando_c);

            double T_B_M,T_S_B,T_FM_I;
            #pragma omp parallel reduction(+:T_B_M,T_S_B,T_FM_I)
            for(long j= 0; j< repeticiones; j++){
                auto start_time= std::chrono::high_resolution_clock::now();
                std::string comando2 = "./boyer.exe";
                const char* comando_2c = comando2.c_str();
                int resultado = system(comando_2c);
                auto stop_time= std::chrono::high_resolution_clock::now();
                auto time    = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time-start_time).count();
                T_B_M+=time;
            }
            for(long j= 0; j< repeticiones; j++){
                auto start_time= std::chrono::high_resolution_clock::now();
                std::string comando2 = "./sufix.exe";
                const char* comando_2c = comando2.c_str();
                int resultado = system(comando_2c);
                auto stop_time= std::chrono::high_resolution_clock::now();
                auto time    = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time-start_time).count();
                T_S_B+=time;
            }
            std::cout<<T_B_M/repeticiones<<","<<T_S_B/repeticiones<<","<<T_FM_I/repeticiones<<"\n";  
        }
    }


    return 0;
}
