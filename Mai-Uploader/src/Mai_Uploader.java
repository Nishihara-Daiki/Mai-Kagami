
import java.io.File;
import java.util.Calendar;

/*
 * 参考ページ
 *  https://developers.google.com/youtube/v3/code_samples/java?hl=ja#upload_a_video 
 */

/*
 * ファイル監視~youtubeアップロードまでのプロセスの説明をします
 * 1.tempフォルダを空フォルダにする
 * 2.videoフォルダを監視(dirMonitor.start())。ファイルが追加されたらtempに移動
 * 3.mainクラスでtempフォルダを監視。
 * 4.tempが空フォルダじゃなくなったらそのファイルのアップロードにうつる
 * 5．アップロードが終わったらそのファイルを消し1に戻る(2については常に動いている)
 */

public class Mai_Uploader {
	public static void main(String[] args) {
		MyYouTube myYoutube = new MyYouTube();
		
		while(true){
			//videoフォルダが空フォルダじゃなくなるまでループ
			File video = new File("./video");
			//videoフォルダに入っているファイルのリスト
			File[] fileList = video.listFiles();
			while(fileList.length == 0){
				fileList = video.listFiles();
			}
			myYoutube.sleep(1000);
			
			try {
				//ファイルに情報を追加する
				myYoutube.setMetadata(
						fileList[0],
						"Mai_Uploader test upload on "  + Calendar.getInstance().getTime(),
						"舞鏡の動画のテストアップロード " + "on " + Calendar.getInstance().getTime()
						);
//				fileList[0].delete();
				System.exit(0);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
 	}
}