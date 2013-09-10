import java.io.*;
import java.util.*;
/*
	Solve.java
	https://codeiq.jp/ace/joboffer_apli/q446 (��n��)�������v���O����
	���m�̐���m�l�A���l�̐���n�̂Ƃ���B
	���j:���ꂼ��݂̊ɕ��m��x�l�A���l��y�́A�{�[�g��(�����瑤:z=0|��������:z=1)�ɂ���A�ƌ�����Ԃ�_(x+(m+1)*y+z*(m+1)*(n+1))�Ԃŕ\��(�v2*(m+1)*(n+1)��)�B
	���ꂼ��̏�Ԃ���ʂ̏�Ԃ֑J�ڂł���Ƃ��ɁA�e��Ԃ�\���_�̊Ԃɖ��������B
	�ŒZ�̉��Ɍ���Ȃ���Ζ����̉������݂���(���ʂȈړ����J��Ԃ��΂悢)�̂ŁA�ŒZ�̉��݂̂����ׂċ��߂�B
*/

public class Solve{
	private int m,n;//���m�̐�,���l�̐�
	private int np;//2(m+1)(n+1),�_�̐�
	private boolean[][] edges;//�ӂ̗L���Atrue:����Afalse:�Ȃ�
	/*
		������(m:���m�̐�,n:���l�̐�,boat:�{�[�g�ɏ��镺�m�E���l�̐�)
	*/
	Solve(int m,int n,int boat){
		if(m<n){
			throw new IllegalArgumentException("���m�̕������Ȃ�");
		}
		this.m=m;
		this.n=n;
		this.np=2*(m+1)*(n+1);
		this.edges=new boolean[np][np];
		//false���߁B���͕K�v�Ȃ�
		for(boolean[] row:edges){
			Arrays.fill(row,false);
		}
		/*�{�[�g�ɏ�镺�m,���l�̐���(k,l)�Ƃ����(k==0�܂���k>=l)����k+l<=boat�A���̏ꍇ��boat=2�Ȃ̂őO���̐����͖����̂Ɠ���*/
		/*�{�[�g�������瑤�ɂ���ꍇ*/
		for(int i=0;i<=m;i++){ //�����瑤�̕��m�̐�
			for(int j=0;j<=n;j++){ //���l�̐�
				if(!isValid(i,j))continue; //�J�ڑO�̏�Ԃ��ǂ����ǂ���
				int p1=toPoint(i,j,0); //�J�ڑO�̓_
				for(int k=0;k<=boat;k++){ //�{�[�g�ɏ�镺�m�̐�
					for(int l=0;l<=boat-k;l++){ //�{�[�g�ɏ�鋐�l�̐�
						if(k>=1 && k<l)continue; //�{�[�g���ő�S���s��
						if(!isValid(i-k,j-l))continue; //�J�ڌ�̏�Ԃ��ǂ����ǂ���
						int p2=toPoint(i-k,j-l,1);
						edges[p1][p2]=true;
					}
				}
			}
		}
	}
	/*
		�e�݂ɂ����镺�m�̐��̐������𒲂ׂ�
		soldier:�����瑤�̕��m�̐�
		titan:�����瑤�̋��l�̐�
	*/
	boolean isValid(int soldier,int titan){
		return soldier>=0 && titan>=0 && //�����瑤�ŕ��m�Ƌ��l�̐�������0�ȏォ�ǂ���
			soldier<=m && titan<=n && //���������ŕ��m�Ƌ��l�̐�������0�ȏォ�ǂ���
			(soldier>=titan || soldier==0)&& //�����瑤�ŕ��m�̕��������܂���0�l���ǂ���
			(m-soldier>=n-titan || m-soldier==0); //���������ŕ��m�̕��������܂���0�l���ǂ���
	}
	/*
		��Ԃ�\���_�̔ԍ���Ԃ��B
		soldier:�����瑤�̕��m�̐�
		titan:�����瑤�̋��l�̐�
		boatplace:�{�[�g��������Ȃ�0,�������Ȃ�1
	*/
	private int toPoint(int soldier, int titan, int boatplace){
		assert isValid(soldier,titan);
		return soldier+(m+1)*titan+(m+1)*(n+1)*boatplace;
	}
	/*
		���蓾��������ׂČ�����
		�����邾���ŏo�͂͂��Ȃ�
	*/
	public void solve(){
		
	}
	public void print(){
	}
	protected void debugPrint(){
		int v=(m+1)*(n+1);
		for(int x=0;x<v;x++){
			int i=x%(m+1);
			int j=x/(m+1);
			System.out.print(isValid(i,j)?"o ":"x ");
		}
		System.out.println();
		for(int i=0;i<v;i++){
			for(int j=0;j<v;j++){
				System.out.print(edges[i][j+v]?"* ":". ");
			}
			System.out.println();
		}
	}
	/*
		����args�͖��������B
	*/
	public static void main(String[] args){
		int m=3;//���m�̐�
		int n=3;//���l�̐�
		int boat=2; // �{�[�g�ɏ���l���̐�
		assert m>=n;//���m�̕��������Ȃ���ΐ�΂ɕs�\
		Solve sol=new Solve(m,n,boat);//������
		sol.debugPrint();//�f�o�b�O�v�����g
		sol.solve();//�������ׂċ��߂�
		sol.print();//�������ׂďo��
	}
}