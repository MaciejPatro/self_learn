pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
		        sh 'cmake -D CMAKE_CXX_COMPILER=clang++ .'
		        sh 'make -j 4'
            }
        }
        stage('Running UTs') {
            steps {
                sh 'exercises/ut/exercisesTests -r junit > ut_results.xml'
            }
        }
        stage('Sanity Check') {
            steps {
                parallel(
                    Address: {
                        sh 'cmake -D CMAKE_CXX_COMPILER=clang++ -D asan=ON .'
                  	    sh 'make'
                        sh 'exercises/ut/exercisesTests -r junit > ut_results.xml'
                    },
                    b: {
                        echo "This is branch b"
                    }
                )
		    }
        }
        stage('Build Product') {
            steps {
                sh 'cmake -D testing=OFF -D CMAKE_CXX_COMPILER=clang++ .'
                sh 'make -j 4'
            }
        }
    }
    post {
        always {
	    junit 'ut_results.xml'
	}
    }
}