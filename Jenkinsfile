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