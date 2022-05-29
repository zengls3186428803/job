//生产者消费者问题 ------双缓冲

typedef int item;
typedef int semaphore;

const int MAX_N = 1e3 + 10;
int n = MAX_N - 1;
int cnt_buf = 2;//缓冲区数量 
struct Buf {
	Buf() {
		empty = n;
		full = 0;
		in = out = 0;
	}
	item buffer[MAX_N];//缓冲区 
	semaphore mutex, empty, full;
	int in, out;
} buf[cnt_buf];//缓冲区信息

void producer() {
	do {
		生产m个产品nextp
		
		//判断能否放下m个产品 
		int empty = 0;
		for(int i = 0; i < cnt_buf; ++i) empty += buf[i].empty
		if(m > empty) 把该进程放入阻塞队列 
		int cnt[cnt_buf] = {0};//记录每个缓冲区应用掉的item数量 
		for(int i = 0; i < cnt_buf; ++i) {
			if(m <= buf[i].empty) {
				cnt[i] = m;
				buf[i].empty -= m;
				m -= cnt[i];
			} else {
				cnt[i] = buf[i].empty;
				buf[i].empty = 0;
				m -= cnt[i];
			}
		}
		
		for(int i = 0; i < cnt_buf; ++i) {
			Swait(buf[i].empty, cnt[i], cnt[i], buf[i].mutex, 1, 1);
		}
		for(int i = 0; i < cnt_buf; ++i) {
			for(int j = 0; j < cnt[i]; ++j) {
				buf[i].buffer[buf[i].in] = nextp;
				buf[i].in = (buf[i].in + 1) % n;
			}
		}
		for(int i = 0; i < cnt_buf; ++i) {
			Ssignal(buf[i].mutex, 1,1, buf[i].full, cnt[i], cnt[i]);
		}
	} while(true);
}

void consumer() {
	//消费t个产品 
	do {
		int full = 0;
		for(int i = 0; i < cnt_buf; ++i) full += buf[i].full;
		if(t > full) 把该进程放入阻塞队列
		int cnt[cnt_buf] = {0};
		for(int i = 0; i < cnt_buf; ++i) {
			if(t <= buf[i].full) {
				cnt[i] = t;
				buf[i].full -= t;
				t -= cnt[i];
			} else {
				cnt[i] = buf[i].full;
				buf[i].full = 0;
				t -= cnt[i];
			}
		}
		
		for(int i = 0; i < cnt_buf; ++i) {
			Swait(buf[i].full, cnt[i], cnt[i], buf[i].mutex, 1,1);
		}
		for(int i = 0; i < cnt_buf; ++i) {
			for(int j = 0; j < cnt[i]; ++j) {
				nextc = buf[i].buffer[buf[i].out];
				buf[i].out = (buf[i].out + 1) % n;
			}
		}
		for(int i = 0; i < cnt_buf; ++i) {
			Ssignal(buf[i].mutex, 1, 1, buf[i].empty, cnt[i], cnt[i]);
		}
	} while(true);
}
