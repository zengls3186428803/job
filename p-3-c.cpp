//���������������� ------ ������������һ��

typedef int item;
typedef int semaphore;

const int MAX_N = 1e3 + 10;
int n = MAX_N - 1;
int cnt_buf = 2;//����������
struct Buf {
	Buf() {
		empty = n;
		full = 0;
		in = out = 0;
	}
	item buffer[MAX_N];//������
	semaphore mutex, empty, full;
	int in, out;
} buf[cnt_buf];//��������Ϣ

int cnt_pc = �����������ѡ��ߵ�����;
int cnt_block = 0;//�����������̵���������ֹ����

void producer_and_consumer() {
	do {
		���������������ѣ� ����������flag = 1�� ���� flag = 0;
		if(flag = 1) {
			����m����Ʒnextp
			//�ж��ܷ����m����Ʒ
			int empty = 0;
			for(int i = 0; i < cnt_buf; ++i) empty += buf[i].empty;
			if(m > empty) {
				if(cnt_block + 1 < cnt_pc) {
					�Ѹý��̷�����������;
					cnt_block += 1;
				} else continue; //��֤������һ��������
			}
			int cnt[cnt_buf] = {0};//��¼ÿ��������Ӧ�õ���item����
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
			//����t����Ʒ
			int full = 0;
			for(int i = 0; i < cnt_buf; ++i) full += buf[i].full;
			if(t > full) {
				if(cnt_block + 1 < cnt_pc) {
					�Ѹý��̷�����������;
					cnt_block += 1;
				} else continue; //��֤������һ�������ߣ�
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
