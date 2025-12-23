#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 500

// 歌曲节点结构体
typedef struct Song {
    int id;
    char title[100];
    char artist[50];
    char filepath[300];
    struct Song* prev;
    struct Song* next;
} Song;

// 播放列表管理器
typedef struct PlaylistManager{
    Song* head;
    Song* tail;
    Song* current;
    int song_count;
} PlaylistManager;

// 函数声明
void init_playlist_manager(PlaylistManager* manager);                           // 初始化链表
int load_songs_from_file(PlaylistManager* manager, const char* filename);       // 从文件中读取到链表
void add_song(PlaylistManager* manager, const char* title, const char* artist,  // 人工增加音乐
              const char* filepath);
int delete_song_by_title(PlaylistManager* manager, const char* title);                   // 删除指定名字的音乐
int play_song_by_title(PlaylistManager* manager, const char* title);                     // 根据名字播放音乐
void display_playlist(PlaylistManager* manager);                                // 显示播放列表（正向）
void display_playlist_reverse(PlaylistManager* manager);                        // 显示播放列表（反向）
int export_playlist(PlaylistManager* manager, const char* filename);            // 导出歌单
void next_song(PlaylistManager* manager);                                       // 下一首歌
void previous_song(PlaylistManager* manager);                                   // 上一首歌
int play_song_random(PlaylistManager* manager);                                 // 随机播放音乐（非必做）
int insert_song_at(PlaylistManager* manager, int position, const char* title, const char* artist, const char* filepath);    // 向指定位置添加音乐（非必做）
void clear_playlist(PlaylistManager* manager);                                  // 清空播放列表（非必做）
void sort_by_title(PlaylistManager* manager);                                   // 按照歌曲名排序（非必做）


// linux/Mac 版本
// void play_audio(const char* filename) {
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Founded File!!");
//     }
//     snprintf(command, sizeof(command), "afplay \"%s\"", filename);
//     int ret = system(command);
//     if (ret != 0) {
//         printf("播放失败或中断，请检查文件格式是否支持。\n");
//     }
// }

// Windows 版本
void play_audio(const char* filename){
    char command[256];
    FILE *mp3File = fopen(filename, "rb");
    if (!mp3File) {
        printf("无法打开文件 %s\n", filename);
        return;
    }
    else{
        printf("Founded File!!");
    }
    snprintf(command, sizeof(command), "start \"\" \"%s\"", filename);
    int ret = system(command);
    if (ret != 0) {
        printf("播放失败或中断，请检查文件格式是否支持。\n");
    }

//     // 或者使用 Windows Media Player
//     // sprintf(command, "wmplayer \"%s\"", filename);
//     // system(command);
}

// void play_audio(const char* filename){
//     printf("Playing %s ...", filename);
// }

// 初始化播放管理器
void init_playlist_manager(PlaylistManager* manager){
    manager->head = NULL;
    manager->tail = NULL;
    manager->current = NULL;
    manager->song_count = 0;
}

// 从文件读取内容构建双向链表
int load_songs_from_file(PlaylistManager* manager, const char* filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
 	{ 
        printf("Failure to open the file\n");
        return -1;
    }
    char *line = (char*)malloc(MAX_SIZE*sizeof(char));
    if (line == NULL) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return -1;
    }
    while(fgets(line, MAX_SIZE, fp) != NULL){
        size_t len = strlen(line);
    	if (len > 0 && line[len-1] == '\n') {
        	line[len-1] = '\0';  // 去掉 \n
    	}
        Song *new_node = (Song*)malloc(sizeof(Song));
        if(new_node == NULL){
            printf("Node allocation failed\n");
            free(line);
            fclose(fp);
            break;
        }
        new_node->prev = NULL;
        new_node->next = NULL;
        if(sscanf(line, "%99[^,],%49[^,],%299[^,]", new_node->title, new_node->artist, new_node->filepath)==3){
            printf("Loaded: %s %s %s\n", new_node->title, new_node->artist, new_node->filepath);
            // 对象为字符串，使用sscanf。对象为文件，使用fscanf。
            manager->song_count++; 
            if(manager->head == NULL){
                manager->head = new_node;
                manager->tail = new_node;
            }else{
                manager->tail->next = new_node;
                new_node->prev = manager->tail;
                manager->tail = new_node;
            }
        }
    }
    return 0;
}

// 1. 在链表末尾添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, const char* filepath) {
    Song *new_node = (Song*)malloc(sizeof(Song));
    if(new_node == NULL){
        printf("Node allocation failed\n");
        return ;
    }
    new_node->prev = NULL;
    new_node->next = NULL;
    strcpy(new_node->title,title);
    strcpy(new_node->artist,artist);
    strcpy(new_node->filepath,filepath);
    if(manager->head == NULL){
        manager->head = new_node;
        manager->tail = new_node; // 原链表为空时
    }else{
        manager->tail->next = new_node;
        new_node->prev = manager->tail;
        manager->tail = new_node;
    }
    manager->song_count++;
    return;
}

// 2. 按标题删除歌曲
int delete_song_by_title(PlaylistManager* manager, const char* title) {
    Song* prev = NULL;
    Song* curr = manager->head;
    if(curr == NULL){
        printf("The queue is empty and cannot be deleted.");
        return -1;
    }
    while(curr != NULL && strcmp(curr->title, title) != 0){
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Song with title '%s' not found.\n", title);
        return -1; // 这是未找到歌曲的情况
    }
    // 以下均为找到歌曲情况
    if(prev == NULL){
        manager->head = curr->next; // 第一首歌就为目标歌曲
        if (manager->head != NULL) {
            manager->head->prev = NULL;
        } else {
            manager->tail = NULL; // 若删除后链表为空，尾指针记得置空
        }
    }else{
        curr->next->prev = prev;
        prev->next = curr->next;
        if(curr == manager->tail){
            manager->tail = prev; // 目标歌曲为最后一首歌
        }
    }
    free(curr);
    manager->song_count--;  // 歌曲数减1
    return 0;
}

// 3. 播放歌曲
int play_song_by_title(PlaylistManager* manager, const char* title){
    Song* curr = manager->head;
    if(curr == NULL){
        printf("The queue is empty and cannot be played.");
        return -1;
    }
    while(curr != NULL && strcmp(curr->title, title) != 0){
        curr = curr->next;
    }
    if(curr == NULL){
        printf("No song found.");
        return -1;
    }
    manager->current = curr;
    play_audio(curr->filepath);
    return 0;
}

// 4. 显示播放列表（正向遍历）
void display_playlist(PlaylistManager* manager) {
    Song *temp=manager->head;
    if(temp == NULL){
        printf("The queue is empty\n");
        return ;
    }
    while(temp != NULL){
        printf("%s,%s,%s\n",temp->title,temp->artist,temp->filepath);
        temp = temp->next;
    }
    return;
}

// 5. 显示播放列表（反向遍历）
void display_playlist_reverse(PlaylistManager* manager) {
    Song *temp=manager->tail;
    if(temp == NULL){
        printf("The queue is empty\n");
        return ;
    }
    while(temp != NULL){
        printf("%s,%s,%s\n",temp->title,temp->artist,temp->filepath);
        temp = temp->prev;
    }
    return;
}

// 6. 将播放列表保存到文件
int export_playlist(PlaylistManager* manager, const char* filename) {
    if(manager == NULL || manager->head == NULL){
        printf("The list is empty.\n");
        return -1;
    }
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
 	{ 
        printf("Failure to open the file\n");
        return -1;
    }
    Song *temp = manager->head;
    while(temp != NULL){
        fprintf(fp, "%s,%s,%s\n", temp->title, temp->artist, temp->filepath);
        // fprintf是在写入文件
        temp = temp->next;
    }
    fclose(fp);
    return 0;
}

// 7. 下一首
void next_song(PlaylistManager* manager) {
    if (manager == NULL || manager->current == NULL) {
        printf("No song is playing now.\n");
        return;
    }
    if(manager->current->next == NULL){
        printf("This is the last song.\n");
        return ;
    }
    manager->current = manager->current->next;
    play_audio(manager->current->filepath);
    return;
}

// 8. 上一首
void previous_song(PlaylistManager* manager) {
    if (manager == NULL || manager->current == NULL) {
        printf("No song is playing now.\n");
        return;
    }
    if(manager->current->prev == NULL){
        printf("This is the first song.\n");
        return ;
    }
    manager->current = manager->current->prev;
    play_audio(manager->current->filepath);
    return;
}

// 9. 随机播放歌曲（非必做）
int play_song_random(PlaylistManager* manager) {
    return 0;
}

// 10. 在指定位置插入歌曲（非必做）
int insert_song_at(PlaylistManager* manager, int position, const char* title,
                   const char* artist, const char* filepath) {
    return 1;
}

// 12. 按歌曲标题排序（非必做）
void sort_by_title(PlaylistManager* manager) {
    return;
}

// 销毁整个链表
void clear_playlist(PlaylistManager* manager) {
    Song* current = manager->head;
    while (current != NULL) {
        Song* next = current->next;
        free(current);
        current = next;
    }
    init_playlist_manager(manager);
    printf("播放列表已清空\n");
}


void display_menu() {
    printf("\n");
    printf("链表音乐播放器管理器\n");
    printf("==========================================\n");
    printf("1. 添加歌曲\n");
    printf("2. 删除歌曲 (按标题)\n");
    printf("3. 播放歌曲 (按标题)\n");
    printf("4. 显示播放列表 (正向)\n");
    printf("5. 显示播放列表 (逆向)\n");
    printf("6. 导出歌单\n");
    printf("7. 切换到下一首歌\n");
    printf("8. 切换到上一首歌\n");
    printf("9. 随机播放歌曲(非必做)\n");
    printf("10. 在指定位置添加歌曲(非必做)\n");
    printf("11. 清空播放列表(非必做)\n");
    printf("12. 按照歌曲名排序(非必做)\n");
    printf("0. 退出程序\n");
    printf("==========================================\n");
    printf("请选择操作 (0-12): ");
}

// 清除输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 获取用户输入的字符串
void get_user_input(char* buffer, int size, const char* prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);

    // 去除换行符
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

// 主函数 - 交互式程序
int main() {
    PlaylistManager manager;
    init_playlist_manager(&manager);
    load_songs_from_file(&manager,"song_list.txt");

    printf("=== 双向链表音乐播放器管理器 ===\n");
    printf("已加载 %d 首示例歌曲\n", manager.song_count);
    manager.current = manager.head;
    int choice;
    char input[100];

    do {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            printf("无效输入，请输入数字\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {                   // 添加歌曲
                char title[100], artist[50], filepath[300];

                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                clear_input_buffer();

                add_song(&manager, title, artist, filepath);
                break;
            }
            case 2: {                   // 删除歌曲 (按标题)
                char title[100];
                get_user_input(title, sizeof(title), "请输入要删除的歌曲标题: ");
                int res = delete_song_by_title(&manager, title);
                break;
            }
            case 3: {                   // 播放歌曲（按歌曲名）
                char title[100];
                get_user_input(title, sizeof(title), "请输入要播放的歌曲标题: ");
                int res = play_song_by_title(&manager, title);
                break;
            }
            case 4: {                   // 显示播放列表（正向）
                display_playlist(&manager);
                break;
            }
            case 5: {                   // 显示播放列表（逆向）
                display_playlist_reverse(&manager);
                break;
            }
            case 6: {                   // 导出播放列表
                char path2export[300];
                get_user_input(path2export, sizeof(path2export), "请输入要导出的目标文件名: ");
                int res = export_playlist(&manager, path2export);
                break;
            }
            case 7: {                   // 播放下一首歌曲
                next_song(&manager);
                break;
            }
            case 8: {                   // 播放上一首歌曲
                previous_song(&manager);
                break;
            }
            case 9: {                   // 随机播放歌曲(非必做)
                int res = play_song_random(&manager);
                break;
            }
            case 10: {                  // 在指定位置添加歌曲(非必做)
                char title[100], artist[50], filepath[300];
                int position;
                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                printf("请输入歌曲插入位置: ");
                scanf("%d", &position);
                insert_song_at(&manager, position, title, artist, filepath);
                break;
            }
            case 11: {                  // 清空播放列表(非必做)
                clear_playlist(&manager);
                break;
            }
            case 12: {                  // 按照歌曲名排序(非必做)
                sort_by_title(&manager);
                break;
            }
            case 0: // 退出程序
                printf("感谢使用链表音乐播放器管理器!\n");
                break;
            default:
                printf("? 无效选择，请重新输入\n");
                break;
        }

        // 暂停，让用户看到结果
        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
        }

    } while (choice != 0);

    // 清理内存
    clear_playlist(&manager);

    return 0;
}
