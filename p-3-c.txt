//生产者消费者问题 ------ 生产者消费者一体

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

int cnt_pc = “生产和消费”者的数量;
int cnt_block = 0;//控制阻塞进程的数量，防止死锁

void producer_and_consumer() {
	do {
		决定生产还是消费， 若生产，则flag = 1， 否则 flag = 0;
		if(flag = 1) {
			生产m个产品nextp
			//判断能否放下m个产品
			int empty = 0;
			for(int i = 0; i < cnt_buf; ++i) empty += buf[i].empty;
			if(m > empty) {
				if(cnt_block + 1 < cnt_pc) {
					把该进程放入阻塞队列;
					cnt_block += 1;
				} else continue; //保证至少有一个消费者
			}
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
		} else {
			//消费t个产品
			int full = 0;
			for(int i = 0; i < cnt_buf; ++i) full += buf[i].full;
			if(t > full) {
				if(cnt_block + 1 < cnt_pc) {
					把该进程放入阻塞队列;
					cnt_block += 1;
				} else continue; //保证至少有一个生产者；
			}
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
		}
	} while(true);
}
