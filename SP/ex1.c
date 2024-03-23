#include <iostream>
#include <cstring>
using namespace std;

enum format{
    mp3=0,wav,ogg,flac
};

enum videoCompression{
    x264=0,Theora,AV1
};

class MediaSegment{
        protected:
        char title[101];
        char author[101];
        int duration;
        int size;
        public:
        MediaSegment(char *title="",char *author="",int duration=0,int size=0){
            strcpy(this->title,title);
            strcpy(this->author,author);
            this->duration=duration;
            this->size=size;
        }
        virtual float price()=0;
        virtual ~MediaSegment(){
        }
        friend ostream &operator<<(ostream &o,MediaSegment &m){
            o<<m.title<<" - "<<m.author<<" - "<<m.duration<<" - "<<m.size<<" - "<<m.price()<<endl;
        }
};

class AudioRecording:virtual public MediaSegment{
protected:
int audioFormat;
int numOfChannels;
public:
AudioRecording(char *title="",char *author="",int duration=0,int size=0, int audioFormat=0,int numOfChannels=0): MediaSegment(title,author,duration,size){
this->audioFormat=audioFormat;
this->numOfChannels=numOfChannels;
}
float price(){
    float price=duration*numOfChannels;
    if(audioFormat==3){
        price*=1.5;
    }
    return price;
}
friend ostream &operator<<(ostream &o,AudioRecording &ar){
o<<ar.title<<" - "<<ar.author<<" - "<<ar.duration<<" - "<<ar.size<<" - "<<ar.price()<<endl;
return o;
}
};

class VideoRecording:virtual public MediaSegment{
protected:
int width;
int videoCompression;
public:
VideoRecording(char *title="",char *author="",int duration=0,int size=0,int width=0,int videoCompression=0): MediaSegment(title,author,duration,size){
this->width=width;
this->videoCompression=videoCompression;
}
float price(){
    float price=0.0;
    if(width<=1920){
        price=100;
    }
    if(width>1920){
        price=170;
    }
    if(videoCompression==0){
        price*=1.5;
    }
    if(videoCompression==1){
        price*=0.9;
    }
    return (float)price;
}
friend ostream &operator<<(ostream &o,VideoRecording &vr){
o<<vr.title<<" - "<<vr.author<<" - "<<vr.duration<<" - "<<vr.size<<" - "<<vr.width<<" - "<<vr.price()<<endl;
return o;
}
};

class MusicVideo:public AudioRecording,public VideoRecording{
protected:
char date[9];
public:
MusicVideo(char *title="",char *author="",int duration=0,int size=0,int audioFOrmat=0,int numOfChannels=0,int width=0,int videoCompression=0,char *date=""): MediaSegment(title,author,duration,size),AudioRecording(title,author,duration,size,audioFOrmat,numOfChannels),VideoRecording(title,author,duration,size,width,videoCompression){
strcpy(this->date,date);
}
float price(){
    int numDate=atoi(date);
    float price=AudioRecording::price()+VideoRecording::price();
    if((numDate%10000)>2010){
        price*=1.3;
    }
    return price;
}
friend ostream &operator<<(ostream &o,MusicVideo &mv){
o<<mv.title<<" - "<<mv.author<<" - "<<mv.date<<" - "<<mv.duration<<" - "<<mv.price()<<endl;
return o;
}
};

float total_price(MediaSegment **niza,int n){
    float price=0.0;
    for(int i=0;i<n;i++){
        price+=niza[i]->price();
    }
    return price;
}

MediaSegment& cheapest_music_video(MediaSegment **niza,int n){
int index;
float minPrice;
int flag=0;
for(int i=0;i<n;i++){
MusicVideo *mv=dynamic_cast<MusicVideo*>(niza[i]);
if(mv && flag==0){
minPrice=niza[i]->price();
flag=1;
index=i;
}
if (mv && flag){
if(minPrice>niza[i]->price()){
minPrice=niza[i]->price();
index=i;
}
}
}
return *niza[index];
}

int main() {

    int test_case_num;
    cin>>test_case_num;


    // for MediaSegment
    char title[100];
    char author[1000];
    unsigned int size;
    unsigned int duration;


    // for AudioRecording
    //-------------------
    unsigned short channels;

    // AudioFormat:
    // 0 - mp3
    // 1 - wav
    // 2 - ogg
    // 3 - flac
    unsigned short format;


    // for VideoRecording
    //-------------------
    unsigned short width;

    // VideoCompression:
    // 0 - x264
    // 1 - Theora
    // 2 - AV1
    int compression;


    // for MusicVideo
    //-------------------
    char publication_date[9];


    if (test_case_num == 1){
        cout<<"Testing class AudioRecording and operator<<"<<std::endl;
        cin.get();
        cin.getline(title,100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> format >> channels;

        AudioRecording a(title, author, duration, size, format, channels);

        cout<<a;

    }

    else if (test_case_num == 2){
        cout<<"Testing class VideoRecording and operator<<"<<std::endl;
        cin.get();
        cin.getline(title,100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> width >> compression;

        VideoRecording v(title, author, duration, size, width, compression);

        cout<<v;

    }

    else if (test_case_num == 3){
        cout<<"Testing class MusicVideo and operator<<"<<std::endl;

        cin.get();
        cin.getline(title,100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;

        cin >> format >> channels;
        cin >> width >> compression;

        cin.get();
        cin.getline(publication_date, 9);
        MusicVideo mv(title, author, duration, size, format, channels, width, compression, publication_date);

        cout << mv;
    }

    else if (test_case_num == 4){
        cout<<"Testing function: total_price "<<std::endl;

        MediaSegment ** m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment*[num_media_segments];

        for (int i=0; i<num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title,100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch(media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression, publication_date);
                    break;
            }
        }

        //for (int i=0;i<num_media_segments; i++){
        //    cout << *m[i];
        //}

        cout<< "Total price is: " << total_price(m, num_media_segments);

        delete [] m;

    }
    else if (test_case_num == 5){
        cout<<"Testing function: cheapest_music_video "<<std::endl;

        MediaSegment ** m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment*[num_media_segments];

        for (int i=0; i<num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title,100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch(media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression, publication_date);
                    break;
            }
        }

        cout << cheapest_music_video(m, num_media_segments);

        delete [] m;
    }

    return 0;
}